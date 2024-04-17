// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ActorSpawner.generated.h"

UCLASS()
class UECOURSE_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AActorSpawner();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Spawn();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	TArray<AActor*> SpawnedObjects;
};
