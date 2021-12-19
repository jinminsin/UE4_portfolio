// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDecideCharacterDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipWeapon, EWeaponType, WeaponType, class UTexture*, WeaponIcon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowCharacterNotice, FText, NoticeString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetProgressbar, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoFarmingCurrentWeapon, class AWeapon*, CurWeapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEZOMBIES_API UPlayerStatus : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TArray<class AItem*> FocusingItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		class AWeapon* CurWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		class AGun* MainWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		class AGun* SubWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		class AWeapon* Knife;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		class AGenerade* Generade;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float CurrentHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float MaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float CurrentSP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float MaxSP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float Armor;

public:	
	// Sets default values for this component's properties
	UPlayerStatus();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	UFUNCTION()
		void AddFocusingItem(class AItem* CurItem);
	UFUNCTION()
		void RemoveFocusingItem(class AItem* CurItem);

	UFUNCTION()
		void AttackCurrentWeapon();

public:
	FOnShowCharacterNotice OnShowCharacterNotice;
	FOnDoFarmingCurrentWeapon OnDoFarmingCurrentWeapon;
	FOnDecideCharacterDeath OnDecideCharacterDeath;
	FOnSetProgressbar OnSetHP, OnSetSP;
	FOnEquipWeapon OnEquipWeapon;

	void TakeDamage(float Damage);
	void SetHP(float NewHP);
	void SetSP(float NewSP);
	bool GetCanRunning();

	void DoFarmingWeapon();
	void CurrentWeaponToggle();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
