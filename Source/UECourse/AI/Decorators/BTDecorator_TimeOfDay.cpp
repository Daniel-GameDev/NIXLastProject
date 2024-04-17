// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_TimeOfDay.h"
#include "Kismet/GameplayStatics.h"
#include "../CourseAIController.h"
#include "../../UECourseCharacter.h"
#include "../AICharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../UECourseGameMode.h"

bool UBTDecorator_TimeOfDay::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AUECourseGameMode* GameMode = Cast<AUECourseGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (FMath::Floor(GameMode->Hour) >= StartOfActivity && FMath::Floor(GameMode->Hour) < EndOfActivity)
		{
			return true;
		}
	}

	return false;
}