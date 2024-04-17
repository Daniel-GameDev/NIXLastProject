// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_TimeOfDay.generated.h"

UCLASS()
class UECOURSE_API UBTDecorator_TimeOfDay : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Condition, meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float StartOfActivity;

	UPROPERTY(EditAnywhere, Category = Condition, meta = (ClampMin = "0.0", ClampMax = "24.0"))
	float EndOfActivity;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
