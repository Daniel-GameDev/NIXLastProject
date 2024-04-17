// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MenuWidget.generated.h"

UCLASS()
class UECOURSE_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnChangeBackground();

	UFUNCTION(BlueprintCallable)
	void OnPlay();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ChangeBackgroundButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* BackgroundImage;
};
