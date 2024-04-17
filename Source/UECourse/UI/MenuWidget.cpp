// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	if (ChangeBackgroundButton != nullptr)
	{
		ChangeBackgroundButton->OnClicked.AddDynamic(this, &UMenuWidget::OnChangeBackground);
	}

	if (PlayButton != nullptr)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMenuWidget::OnPlay);
	}
}

void UMenuWidget::OnChangeBackground()
{
	FSlateColor Color = FSlateColor(FLinearColor::MakeRandomColor());
	BackgroundImage->SetBrushTintColor(Color);
}

void UMenuWidget::OnPlay()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLevel"));
}