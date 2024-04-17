// Fill out your copyright notice in the Description page of Project Settings.

#include "SessionWidget.h"
#include "../SessionSubsystem.h"

void USessionWidget::CreateSession(int32 NumPublicConnections, bool IsLANMatch, FString LevelName)
{
	SessionSubsystem = GetGameInstance()->GetSubsystem<USessionSubsystem>();
	if (SessionSubsystem)
	{
		if (GetOwningPlayer()->HasAuthority())
		{
			if (!bOnCreateSessionCompleteBound)
			{
				SessionSubsystem->OnCreateSessionCompleteEvent.AddDynamic(this, &USessionWidget::OnCreateSessionComplete);
				bOnCreateSessionCompleteBound = true;
			}
			
			SessionSubsystem->CreateSession(NumPublicConnections, IsLANMatch, LevelName);
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Creating Session.."));
		}
		else
		{
			SessionSubsystem = nullptr;
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Only server is allowed to create a session"));
		}
	}
}

void USessionWidget::OnCreateSessionComplete(bool Successful)
{
	if (Successful && SessionSubsystem)
	{
		SessionSubsystem->StartSession();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Starting Session.."));
	}
	else
	{
		SessionSubsystem = nullptr;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Creating Session Failed"));
	}
}

void USessionWidget::JoinSession(int32 MaxSearchResults, bool isLANQuary)
{
	SessionSubsystem = GetGameInstance()->GetSubsystem<USessionSubsystem>();
	if (SessionSubsystem)
	{
		if (GetOwningPlayer()->HasAuthority())
		{
			if (!bOnFindSessionsCompleteBound)
			{
				SessionSubsystem->OnFindSessionsCompleteEvent.AddDynamic(this, &USessionWidget::OnFindSessionComplete);
				bOnFindSessionsCompleteBound = true;
			}
			
			SessionSubsystem->FindSessions(MaxSearchResults, isLANQuary);
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Try to find Sessions.."));
		}
		else
		{
			SessionSubsystem = nullptr;
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Only server is allowed to join a session"));
		}
	}
}

void USessionWidget::OnFindSessionComplete(const TArray<FBlueprintSessionResult>& SessionsResult, bool Successful)
{
	if (Successful && SessionSubsystem)
	{
		if (SessionsResult.Num() != 0)
		{
			const FBlueprintSessionResult& Session = SessionsResult.Last();;
			SessionSubsystem->JoinGameSession(Session);
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Joining game session.."));
		}
		else
		{
			SessionSubsystem = nullptr;
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("There are no active sessions to join"));
		}
	}
	else
	{
		SessionSubsystem = nullptr;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Unexpetcted error during session search"));
	}
}