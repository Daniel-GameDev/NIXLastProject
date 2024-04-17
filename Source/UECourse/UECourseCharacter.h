// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "UECourseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemCollected, int, HitPoints);

UCLASS(config=Game)
class AUECourseCharacter : public ACharacter//, public IFighterInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AIndicator> IndicatorClass;

public:
	AUECourseCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = Camera)
	float RightInputValue;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = Camera)
	float ForwardInputValue;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = Camera)
	float TurnInputRate;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "State")
	bool bAttack = false;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "State")
	bool bStunned = false;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "Character")
	bool bUseControllerRotationYawReplicated;

	UPROPERTY(EditDefaultsOnly, Category = "State")
	float StunTime = 5.f;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(Server, Reliable)
	void MoveForward(float Value);

	UFUNCTION(Client, Reliable)
	void MoveForward_Client(float Value);
	
	UFUNCTION(Server, Reliable)
	void MoveRight(float Value);

	UFUNCTION(NetMulticast, Reliable)
	void MoveRight_Multicast(float Value);

	// ClawAttack
	UFUNCTION(Server, Reliable, WithValidation)
	void ClawAttack();

	UFUNCTION(NetMulticast, Reliable)
	void ClawAttack_Multicast();

	UFUNCTION(BlueprintCallable)
	void ClawAttackFinished();

	virtual bool ClawAttack_Validate();

	//Stun State
	UFUNCTION(Server, Reliable)
	void StunBegin();

	UFUNCTION(NetMulticast, Reliable)
	void StunBegin_Multicast();

	UFUNCTION(Server, Reliable)
	void StunFinished();

	UFUNCTION(NetMulticast, Reliable)
	void StunFinished_Multicast();

	UFUNCTION(Server, Reliable)
	void StunIndicatorSpawn(FVector Location);

	UFUNCTION(NetMulticast, Reliable)
	void StunIndicatorSpawn_Multicast(FVector Location);

	virtual bool StunBegin_Validate();

	void Turn(float Rate);
	void LookUp(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintPure, Category = "C++")
	FORCEINLINE bool GetAttack() const { return bAttack; }

	UFUNCTION(BlueprintPure, Category = "C++")
	FORCEINLINE bool GetStunned() const { return bStunned; }

	UFUNCTION(BlueprintCallable, Category = Character)
	virtual void ShowInfo();

	UFUNCTION(BlueprintCallable, Category = Character)
	void InvokeDamage(int Damage);

	UFUNCTION(BlueprintCallable, Category = Character)
	int DealDamage();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	void PickUp(AActor* OtherActor);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemCollected OnItemCollected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentHP = 100;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCharacterWidget> PlayerHUDClass;

	UPROPERTY(EditAnywhere)
	class UCharacterWidget* PlayerHUD;

private:
	FTimerHandle StunTimerHandle;

	void Log(FString Name, FString ClassName);

};