// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_InterruptAttack.h"
#include "../CourseAIController.h"
#include "../AICharacter.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_InterruptAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACourseAIController* Controller = Cast<ACourseAIController>(OwnerComp.GetOwner());

	if (Controller != nullptr)
	{
		AAICharacter* Character = Cast<AAICharacter>(Controller->GetPawn());

		if (Character != nullptr)
		{
			Character->IsAttacking = false;
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
