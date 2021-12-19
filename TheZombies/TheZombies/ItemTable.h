// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemTable.generated.h"

USTRUCT(BlueprintType)
struct FMonsterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float BaseArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float BaseDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float BaseHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		int32 rarity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float ArmorIncreasePerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float DamageIncreasePerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float HPIncreasePerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float ArmorValueIncreasePerUpperLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float DamageValueIncreasePerUpperLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float HPValueIncreasePerUpperLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float DetectRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		class UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		class USkeletalMesh* Body;

	FMonsterData() {};
};

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase 
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float BaseHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float BaseSP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float Armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float HPIncreasePerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float SPIncreasePerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		float ArmorIncreasePerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		class UAnimMontage* FireMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		class UAnimMontage* KnifeMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		class UAnimMontage* HitReactMontage;

	FCharacterData() {};
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		int32 ItemRow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FText FlavorText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		int32 CurrentCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		int32 MaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		class UTexture* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		class USkeletalMesh* Body;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FTransform BodyTransform;

	FItemData() {};
};

USTRUCT(BlueprintType)
struct FExpendablesData : public FItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		float EffectAbility;

	FExpendablesData() { Super(); };
};

USTRUCT(BlueprintType)
struct FWeaponData : public FItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		int32 Durability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		class UTexture* WeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FTransform RightHandSocketTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		class UAnimMontage* AttackMontage;

	FWeaponData() { Super(); };
};

USTRUCT(BlueprintType)
struct FGunData : public FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		float Recoil;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		int32 RPM;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FVector LeftHandIKVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
		FVector RightHandIKVector;

	FGunData() { Super(); };
};

UCLASS()
class THEZOMBIES_API UItemTable : public UDataTable
{
	GENERATED_BODY()
	
};
