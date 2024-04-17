// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpSpawner.h"
#include "../UECourseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickUpSpawner::APickUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickUpSpawner::BeginPlay()
{
	Super::BeginPlay();

	AUECourseCharacter* character = Cast<AUECourseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (character != nullptr)
	{
		character->OnItemCollected.AddDynamic(this, &APickUpSpawner::Spawn);
	}

	Spawn(0.f);
}

// Called every frame
void APickUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpSpawner::Spawn(int hp)
{
	if (ItemClass != nullptr)
	{
		FRotator spawnRotation = FRotator();
		FVector spawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(BoxCollision->GetComponentLocation(), BoxCollision->GetScaledBoxExtent());
		spawnLocation.Z = BoxCollision->GetComponentLocation().Z;
		FActorSpawnParameters actorSpawnParameters;

		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		AActor* item;
		do 
		{
			item = GetWorld()->SpawnActor<AActor>(ItemClass, spawnLocation, spawnRotation, actorSpawnParameters);
		} while (item == nullptr);
	}
}