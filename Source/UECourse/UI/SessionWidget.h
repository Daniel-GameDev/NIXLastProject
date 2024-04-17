// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionsCallbackProxy.h"
#include "SessionWidget.generated.h"

UCLASS()
class UECOURSE_API USessionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CreateSession(int32 NumPublicConnections, bool IsLANMatch, FString LevelName);

	UFUNCTION(BlueprintCallable)
	void JoinSession(int32 MaxSearchResults, bool isLANQuary);

private:
	class USessionSubsystem* SessionSubsystem;

	bool bOnCreateSessionCompleteBound = false;
	bool bOnFindSessionsCompleteBound = false;

	UFUNCTION()
	void OnCreateSessionComplete(bool Successful);

	UFUNCTION()
	void OnFindSessionComplete(const TArray<FBlueprintSessionResult>& SessionsResult, bool Successful);

};