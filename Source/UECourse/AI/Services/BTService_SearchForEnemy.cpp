// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchForEnemy.h"
#include "../CourseAIController.h"
#include "../../UECourseCharacter.h"
#include "../AICharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SearchForEnemy::UBTService_SearchForEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Search For Enemy";

	EnemyKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_SearchForEnemy, EnemyKey), AActor::StaticClass());
}

void UBTService_SearchForEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool Seen = false;
	ACourseAIController* Controller = Cast<ACourseAIController>(OwnerComp.GetOwner());

	if (Controller == nullptr)
	{
		return;
	}

	AAICharacter* Character = Cast<AAICharacter>(Controller->GetPawn());

	if (Character == nullptr)
	{
		return;
	}

	float PatrolRadius = Controller->GetPatrolRadius();
	FVector Start = Character->GetActorLocation();
	TArray<FHitResult> OutHits;
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, Start, PatrolRadius, TraceObjectTypes, false, TArray<AActor*>(), EDrawDebugTrace::None, OutHits, true);

	for (FHitResult& HitResult : OutHits)
	{
		if (HitResult.Actor != nullptr)
		{
			AUECourseCharacter* Enemy = Cast<AUECourseCharacter>(HitResult.Actor);

			if (Enemy != nullptr)
			{
				Controller->GetBlackboardComponent()->SetValueAsObject(EnemyKey.SelectedKeyName, Enemy);
				Seen = true;
			}
		}
	}

	if (!Seen)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(Controller->GetDetectedEnemyKey(), nullptr);
	}
}