// Fill out your copyright notice in the Description page of Project Settings.

#include "Indicator.h"
#include "Components/TimelineComponent.h"

AIndicator::AIndicator()
{
	PrimaryActorTick.bCanEverTick = true;

	MovingUpwardsTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
}

void AIndicator::BeginPlay()
{
	Super::BeginPlay();

	SetupAndPlayTimelineForMovingUpwards();
}

void AIndicator::SetupAndPlayTimelineForMovingUpwards()
{
	if (UpwardsCurve && MovingUpwardsTimeline)
	{
		MovingUpwardsTimeline->SetTimelineLength(TimelineLenght);
		MovingUpwardsTimeline->SetLooping(false);

		FOnTimelineFloat UpdateTimelineCallBack;
		UpdateTimelineCallBack.BindUFunction(this, FName(TEXT("UpdateTimeline")));
		MovingUpwardsTimeline->AddInterpFloat(UpwardsCurve, UpdateTimelineCallBack);
		MovingUpwardsTimeline->SetTimelineFinishedFunc(FOnTimelineEventStatic::CreateUObject(this, &AIndicator::TimelineFinished));
		MovingUpwardsTimeline->PlayFromStart();
	}
}

void AIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovingUpwardsTimeline)
	{
		MovingUpwardsTimeline->ReceiveTick(DeltaTime);
	}
}

void AIndicator::UpdateTimeline(float Value)
{
	const FVector OldLocation = GetActorLocation();
	const FVector NewLocation{ OldLocation.X, OldLocation.Y, OldLocation.Z + Value };
	SetActorLocation(NewLocation);
}

void AIndicator::TimelineFinished()
{
	Destroy();
}
