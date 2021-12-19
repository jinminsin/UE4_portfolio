// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "GameFramework/Character.h"
#include "TheZombiesCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDunGeonEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToggleEquipmentAndInventory, int32, TogglePanel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeAutoShoot, bool, AutoShoot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddCurrentItem, class AItem*, CurItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoveCurrentItem, class AItem*, CurItem);

UCLASS(config=Game)
class ATheZombiesCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	class UPlayerStatus* PlayerStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HitReactMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	EStateCharacter CurrentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	bool bBurstAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float RecoilRange;

public:
	ATheZombiesCharacter();

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Run();
	void Walk();
	void InterAction();
	void Attack();
	void ToggleShootingMode();
	void ToggleInventory();
	void ToggleEquipment();
	void ToggleEquipmentAndInventory();
	
	FVector MoveInterpolationVector;
	FVector CurrentLeftHandIKVector;
	FVector CurrentRightHandIKVector;

	UFUNCTION()
		void DrawWeapon(class AWeapon* CurWeapon);

	UFUNCTION()
		void CharacterDeath();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	
public:
	FORCEINLINE class UPlayerStatus* GetPlayerStatus() const { return PlayerStatus; }	
	EStateCharacter GetStateCharacter() const { return CurrentState; }
	bool CanBurstAttack() const { return bBurstAttack; }
	FVector GetCurrentLeftHandIKVector() const { return CurrentLeftHandIKVector; }
	FVector GetCurrentRightHandIKVector() const { return CurrentRightHandIKVector; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FVector GetAimVector(float Range);
	void StopAttack();

	FOnAddCurrentItem OnAddCurrentItem;
	FOnRemoveCurrentItem OnRemoveCurrentItem;
	FOnAttackWeapon OnAttackWeapon;
	FOnChangeAutoShoot OnChangeAutoShoot;
	FOnDunGeonEnd OnDunGeonEnd;
	FOnToggleEquipmentAndInventory OnToggleEquipmentAndInventory;
};

