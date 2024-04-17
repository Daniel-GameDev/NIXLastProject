// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SearchForEnemy.generated.h"

UCLASS()
class UECOURSE_API UBTService_SearchForEnemy : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UBTService_SearchForEnemy(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditInstanceOnly, Category = Default)
	FBlackboardKeySelector EnemyKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
