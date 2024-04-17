// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "CourseAIController.h"
#include "../UI/CharacterWidget.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HP_Widget");
	HPWidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AAICharacter::DealDamage()
{
	return FMath::FRandRange(10, 20);
}

void AAICharacter::Attack()
{
	IsAttacking = true;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAICharacter::EndAttack, 1.f, false);
}

void AAICharacter::EndAttack()
{
	IsAttacking = false;
}

void AAICharacter::Stun()
{
	IsStunned = true;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAICharacter::EndStun, 3.f, false);
}

void AAICharacter::EndStun()
{
	IsStunned = false;
}

void AAICharacter::InvokeDamage(int Damage)
{
	CurrentHP -= Damage;
	CurrentHP = FMath::Clamp(CurrentHP, 0, MaxHP);

	if (HPWidgetComponent != nullptr)
	{
		UCharacterWidget* Widget = Cast<UCharacterWidget>(HPWidgetComponent->GetWidget());

		if (Widget != nullptr)
		{
			Widget->SetHealth(CurrentHP, MaxHP);
		}
	}
}