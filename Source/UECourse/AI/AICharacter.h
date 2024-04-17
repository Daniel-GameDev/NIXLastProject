// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../FighterInterface.h"
#include "Components/WidgetComponent.h"
#include "AICharacter.generated.h"

UCLASS()
class UECOURSE_API AAICharacter : public ACharacter//, public IFighterInterface
{
	GENERATED_BODY()

public:
	AAICharacter();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Character)
	int DealDamage();

	UFUNCTION(BlueprintCallable, Category = Character)
	void InvokeDamage(int Damage);

	UFUNCTION(BlueprintCallable, Category = Character)
	void Attack();

	UFUNCTION(BlueprintCallable, Category = Character)
	void EndAttack();

	UFUNCTION(BlueprintCallable, Category = Character)
	void Stun();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsStunned = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HPWidgetComponent;

protected:
	virtual void BeginPlay() override;

	void EndStun();
};
