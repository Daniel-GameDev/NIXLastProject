// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"
#include "Kismet/GameplayStatics.h"
#include "../UECourseGameMode.h"

// Sets default values
ATimeManager::ATimeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Hour += DeltaTime * 0.1;
	Hour = FMath::Clamp(Hour, 0.f, 24.f);

	if (AUECourseGameMode* GameMode = Cast<AUECourseGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->Hour = Hour;
	}
}

