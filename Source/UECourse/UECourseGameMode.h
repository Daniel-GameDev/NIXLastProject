// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UECourseGameMode.generated.h"

UCLASS(minimalapi)
class AUECourseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUECourseGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	float Hour = 0.f;
};



