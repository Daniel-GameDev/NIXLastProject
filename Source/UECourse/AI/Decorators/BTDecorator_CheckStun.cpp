// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckStun.h"
#include "../CourseAIController.h"
#include "../AICharacter.h"

bool UBTDecorator_CheckStun::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (ACourseAIController* Controller = Cast<ACourseAIController>(OwnerComp.GetAIOwner()))
	{
		AAICharacter* Character = Cast<AAICharacter>(Controller->GetPawn());

		if (Character != nullptr)
		{
			return Character->IsStunned;
		}
		
	}

	return false;
}