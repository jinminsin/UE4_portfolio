// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API AGun : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	float Recoil;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 CurAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 RPM;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* MuzzleEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool AutoShoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool IsFiring;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool IsReFiring;

public:
	AGun();

	virtual void Attack() override;
	void Fire();
	void CanFire();
	void ToggleAutoShoot();

	UFUNCTION()
		void DamageEnemy(class AMonster* Enemy);

	FTimerHandle FireHandle;

	FVector GetLeftHandIKVector() const { return DataTable->FindRow<FGunData>(*FString::FromInt(ItemRow), TEXT(""))->LeftHandIKVector; }

	FVector GetRightHandIKVector() const { return DataTable->FindRow<FGunData>(*FString::FromInt(ItemRow), TEXT(""))->RightHandIKVector; }
};
