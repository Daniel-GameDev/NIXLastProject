// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/UserWidget.h"

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);

		if (MenuWidget != nullptr)
		{
			MenuWidget->AddToViewport();
		}
	}
}

void AMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	if (NewPlayer != nullptr)
	{
		NewPlayer->SetShowMouseCursor(true);
		NewPlayer->SetInputMode(FInputModeUIOnly());
	}
}