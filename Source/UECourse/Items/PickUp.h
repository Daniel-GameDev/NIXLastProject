// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "../PickUpInterface.h"
#include "PickUp.generated.h"

UCLASS()
class UECOURSE_API APickUp : public AActor, public IPickUpInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual int Interact() override;

	UFUNCTION(BlueprintCallable)
	int DoEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	int HitPoints = 0;
};
