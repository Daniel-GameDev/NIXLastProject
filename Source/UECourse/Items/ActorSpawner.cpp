// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TestActor.h"

// Sets default values
AActorSpawner::AActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActorSpawner::Spawn()
{
	if (ItemClass != NULL)
	{
		FRotator spawnRotation = FRotator();
		FVector spawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(BoxCollision->GetComponentLocation(), BoxCollision->GetScaledBoxExtent());
		FActorSpawnParameters actorSpawnParameters;

		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		AActor* item = GetWorld()->SpawnActor<AActor>(ItemClass, spawnLocation, spawnRotation, actorSpawnParameters);
		SpawnedObjects.Emplace(item);

		if (SpawnedObjects.Num() >= 10)
		{
			for (int i = 0; i < SpawnedObjects.Num(); i ++)
			{
				if (SpawnedObjects[i] != nullptr)
				{
					SpawnedObjects[i]->Destroy();
				}
			}

			SpawnedObjects.Empty();
		}
	}
}

// Called every frame
void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
