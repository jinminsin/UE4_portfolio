// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

UCLASS()
class THEZOMBIES_API AWeapon : public AItem
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		float Range;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Infomation)
		int32 Durability;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Icon)
		class UTexture* WeaponIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* AttackMontage;

public:
	FORCEINLINE class UTexture* GetWeaponIcon() const { return WeaponIcon; }

	virtual void Attack();
	virtual FItemData MakeItemData() override;

	FTransform GetRightHandSocketTransform() const { return DataTable->FindRow<FWeaponData>(*FString::FromInt(ItemRow), TEXT(""))->RightHandSocketTransform; }
};
