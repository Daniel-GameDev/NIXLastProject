// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetRandomPoint.h"
#include "../CourseAIController.h"
#include "../AICharacter.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomPoint::UBTTask_GetRandomPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Get Random Point";

	LocationKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetRandomPoint, LocationKey), AActor::StaticClass());
	LocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetRandomPoint, LocationKey));
}

EBTNodeResult::Type UBTTask_GetRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACourseAIController* Controller = Cast<ACourseAIController>(OwnerComp.GetOwner());
	if (Controller == nullptr)
	{
		EBTNodeResult::Failed;
	}

	float PatrolRadius = Controller->GetPatrolRadius();

	if (PatrolRadius > 0.f)
	{
		FNavLocation ResultLocation;

		if (UNavigationSystemV1::GetNavigationSystem(&OwnerComp)->GetRandomReachablePointInRadius(Controller->GetNavAgentLocation(), PatrolRadius, ResultLocation))
		{
			AAICharacter* Character = Cast<AAICharacter>(Controller->GetPawn());
			if (Character == nullptr)
			{
				EBTNodeResult::Failed;
			}

			Controller->GetBlackboardComponent()->SetValueAsVector(Controller->GetLocationKey(), ResultLocation.Location);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
