// Copyright Epic Games, Inc. All Rights Reserved.

#include "UECourseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Items/TestActor.h"
#include "PickUpInterface.h"
#include "Items/PickUp.h"
#include "UI/CharacterWidget.h"
#include "Net/UnrealNetwork.h"
#include "Items/Indicator.h"

//////////////////////////////////////////////////////////////////////////
// AUECourseCharacter

AUECourseCharacter::AUECourseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//bReplicates = true;
	//SetReplicateMovement(true);
}

void AUECourseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AUECourseCharacter::OnOverlapBegin);

	
}

void AUECourseCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UPickUpInterface::StaticClass()))
	{
		PickUp(OtherActor);
	}

	if (!HasAuthority())
	{
		return;
	}

	if (OtherActor && OtherActor != this)
	{
		if (AUECourseCharacter* OtherCourseCharacter = Cast<AUECourseCharacter>(OtherActor))
		{
			if (OtherCourseCharacter->bAttack)
			{
				if (StunBegin_Validate())
				{
					StunBegin();
					StunIndicatorSpawn(OverlappedComponent->GetComponentLocation());
				}
			}
		}
	}
}

void AUECourseCharacter::StunIndicatorSpawn_Implementation(FVector Location)
{
	StunIndicatorSpawn_Multicast(Location);
}

void AUECourseCharacter::StunIndicatorSpawn_Multicast_Implementation(FVector Location)
{
	if (IndicatorClass)
	{
		if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			FVector PlayerCameraLocation;
			FRotator PlayerCameraRotation;
			PlayerController->GetPlayerViewPoint(PlayerCameraLocation, PlayerCameraRotation);
			const FVector DirectionToCamera = PlayerCameraLocation - GetActorLocation();
			const FRotator SpawnRotation = DirectionToCamera.Rotation();

			GetWorld()->SpawnActor<AIndicator>(IndicatorClass, Location, SpawnRotation);
		}
	}
}

bool AUECourseCharacter::StunBegin_Validate()
{
	if (bStunned)
	{
		return false;
	}
	return true;
}

void AUECourseCharacter::StunBegin_Implementation()
{
	if (StunTimerHandle.IsValid())
	{
		StunTimerHandle.Invalidate();
	}
	GetWorldTimerManager().SetTimer(StunTimerHandle, this, &AUECourseCharacter::StunFinished, StunTime, false);

	StunBegin_Multicast();
}

void AUECourseCharacter::StunBegin_Multicast_Implementation()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	bUseControllerRotationYawReplicated = false;
	bUseControllerRotationYaw = bUseControllerRotationYawReplicated;
	bStunned = true;
}

void AUECourseCharacter::StunFinished_Implementation()
{
	StunFinished_Multicast();
}

void AUECourseCharacter::StunFinished_Multicast_Implementation()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bUseControllerRotationYawReplicated = true;
	bUseControllerRotationYaw = bUseControllerRotationYawReplicated;
	bStunned = false;
}

void AUECourseCharacter::PickUp(AActor* OtherActor)
{
	IPickUpInterface* PickUp = Cast<IPickUpInterface>(OtherActor);
	int TakeAHit = PickUp->Interact();

	InvokeDamage(TakeAHit);
	OnItemCollected.Broadcast(TakeAHit);
	OtherActor->Destroy();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUECourseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("ShowInfo", IE_Pressed, this, &AUECourseCharacter::ShowInfo);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUECourseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUECourseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AUECourseCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AUECourseCharacter::LookUp);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AUECourseCharacter::ClawAttack);
}

void AUECourseCharacter::ClawAttack_Implementation()
{
	if (ClawAttack_Validate())
	{
		ClawAttack_Multicast();
	}
}

bool AUECourseCharacter::ClawAttack_Validate()
{
	return !bStunned;
}

void AUECourseCharacter::ClawAttack_Multicast_Implementation()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	bAttack = true;
}

void AUECourseCharacter::ClawAttackFinished()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bAttack = false;
}

void AUECourseCharacter::Turn(float Rate)
{
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		TurnInputRate = Rate;
	}
	else
	{
		TurnInputRate = 0.0f;
	}
	
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUECourseCharacter::LookUp(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUECourseCharacter::MoveForward_Implementation(float Value)
{
	if(GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		ForwardInputValue = Value;

		MoveForward_Client(Value);
	}
	else
	{
		ForwardInputValue = 0.0f;
	}
}

void AUECourseCharacter::MoveForward_Client_Implementation(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUECourseCharacter::MoveRight_Implementation(float Value)
{
	MoveRight_Multicast(Value);
}

void AUECourseCharacter::MoveRight_Multicast_Implementation(float Value)
{
	if(GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		RightInputValue = Value;

		if ( (Controller != nullptr) && (Value != 0.0f) )
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
	
			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
	else
	{
		RightInputValue = 0.0f;
	}
}

void AUECourseCharacter::ShowInfo()
{
	TArray<AActor*> AllActorsOfClass;
	AActor* ActorOfClass;
	TArray<AActor*> AllActorsOfClassWithTag;
	TArray<AActor*> AllActorsWithTag;
	UWorld* World = GetWorld();

	UGameplayStatics::GetAllActorsOfClass(World, ATestActor::StaticClass(), AllActorsOfClass);
	ActorOfClass = UGameplayStatics::GetActorOfClass(World, ATestActor::StaticClass());
	UGameplayStatics::GetAllActorsOfClassWithTag(World, ATestActor::StaticClass(), FName(TEXT("ActorOfClassTag")), AllActorsOfClassWithTag);
	UGameplayStatics::GetAllActorsWithTag(World, FName(TEXT("ActorTag")), AllActorsWithTag);

	UE_LOG(LogTemp, Warning, TEXT("GetAllActorsOfClass()"));
	for (AActor* Actor : AllActorsOfClass)
	{
		Log(Actor->GetFName().ToString(), Actor->GetClass()->GetFName().ToString());
	}

	if (ActorOfClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetActorOfClass()"));
		Log(ActorOfClass->GetFName().ToString(), ActorOfClass->GetClass()->GetFName().ToString());
	}

	UE_LOG(LogTemp, Warning, TEXT("GetAllActorsOfClassWithTag()"));
	for (AActor* Actor : AllActorsOfClassWithTag)
	{
		Log(Actor->GetFName().ToString(), Actor->GetClass()->GetFName().ToString());
	}

	UE_LOG(LogTemp, Warning, TEXT("GetAllActorsµøWithTag()"));
	for (AActor* Actor : AllActorsWithTag)
	{
		Log(Actor->GetFName().ToString(), Actor->GetClass()->GetFName().ToString());
	}
}

void AUECourseCharacter::Log(FString Name, FString ClassName)
{
	UE_LOG(LogTemp, Warning, TEXT("Found an actor - %s - %s "), *Name, *ClassName);
}

int AUECourseCharacter::DealDamage()
{
	return FMath::FRandRange(10, 20);
}

void AUECourseCharacter::InvokeDamage(int Damage)
{
	CurrentHP -= Damage;
	CurrentHP = FMath::Clamp(CurrentHP, 0, MaxHP);

	if (PlayerHUD != nullptr)
	{
		PlayerHUD->SetHealth(CurrentHP, MaxHP);
	}

	if (CurrentHP <= 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("LevelMenu"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Actor take a hit for %d points"), Damage);
}

void AUECourseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUECourseCharacter, ForwardInputValue);
	DOREPLIFETIME(AUECourseCharacter, RightInputValue);
	DOREPLIFETIME(AUECourseCharacter, TurnInputRate);
	DOREPLIFETIME(AUECourseCharacter, bAttack);
	DOREPLIFETIME(AUECourseCharacter, bStunned);
	DOREPLIFETIME(AUECourseCharacter, bUseControllerRotationYawReplicated);
}
