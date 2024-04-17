// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indicator.generated.h"

UCLASS()
class UECOURSE_API AIndicator : public AActor
{
	GENERATED_BODY()
	
public:
	AIndicator();

protected:
	virtual void BeginPlay() override;

	void SetupAndPlayTimelineForMovingUpwards();

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Timeline")
	UCurveFloat* UpwardsCurve;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Timeline")
	float TimelineLenght = 3.f;

	UFUNCTION()
	void UpdateTimeline(float Value);

	UFUNCTION()
	void TimelineFinished();

	class UTimelineComponent* MovingUpwardsTimeline;

};
