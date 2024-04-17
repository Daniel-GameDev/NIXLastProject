// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "EnemyWidget.generated.h"

UCLASS()
class UECOURSE_API UEnemyWidget : public UUserWidget
{
	GENERATED_BODY()

	void SetHealth(int currentHaelth, int maxHealth);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HealthBar;
};
