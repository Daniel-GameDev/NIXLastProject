// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetSpeed.h"
#include "../CourseAIController.h"
#include "../../UECourseCharacter.h"
#include "../AICharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_SetSpeed::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	ACourseAIController* Controller = Cast<ACourseAIController>(SearchData.OwnerComp.GetOwner());
	AAICharacter* Character = Cast<AAICharacter>(Controller->GetPawn());

	if (Character != nullptr)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
}