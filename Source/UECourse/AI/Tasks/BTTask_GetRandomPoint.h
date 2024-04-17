// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetRandomPoint.generated.h"

UCLASS()
class UECOURSE_API UBTTask_GetRandomPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_GetRandomPoint(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditInstanceOnly, Category = Default)
	FBlackboardKeySelector LocationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
