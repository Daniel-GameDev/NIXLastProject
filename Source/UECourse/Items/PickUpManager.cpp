// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpManager.h"
#include "../UECourseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APickUpManager::APickUpManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUpManager::BeginPlay()
{
	Super::BeginPlay();
	
	AUECourseCharacter* character = Cast<AUECourseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (character != nullptr)
	{
		character->OnItemCollected.AddDynamic(this, &APickUpManager::Log);
	}
}

void APickUpManager::Log(int hp)
{
	AUECourseCharacter* character = Cast<AUECourseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (character == nullptr)
	{
		return;
	}

	if (GEngine)
	{
		if (hp > 0.f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Character has been healed by %d. Current HP = %d"), hp, character->CurrentHP));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Character has been damaged by %d. Current HP = %d"), hp, character->CurrentHP));
		}
	}
}

// Called every frame
void APickUpManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}