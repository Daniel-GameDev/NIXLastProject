// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../UI/MenuWidget.h"
#include "MenuGameMode.generated.h"

UCLASS()
class UECOURSE_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> MenuWidgetClass;

	UPROPERTY(EditAnywhere)
	class UMenuWidget* MenuWidget;

protected:
	virtual void BeginPlay() override;
};
