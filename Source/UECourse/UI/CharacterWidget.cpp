// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWidget.h"

void UCharacterWidget::SetHealth(int currentHaelth, int maxHealth)
{
	if (HealthBar != nullptr)
	{
		HealthBar->SetPercent((float)currentHaelth / maxHealth);
	}
}