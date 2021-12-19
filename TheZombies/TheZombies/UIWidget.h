// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UUIWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Meta = (WidgetBind))
		class UProgressBar* HPbar;

	UPROPERTY(Meta = (WidgetBind))
		class UProgressBar* SPbar;

	UPROPERTY(Meta = (WidgetBind))
		class UTextBlock* HP;
	
	UPROPERTY(Meta = (WidgetBind))
		class UTextBlock* SP;

	UPROPERTY(Meta = (WidgetBind))
		class UTextBlock* CharacterNotice;

	UPROPERTY(Meta = (WidgetBind))
		class UTextBlock* CurrentEquipNum;

	UPROPERTY(Meta = (WidgetBind))
		class UTextBlock* MaxEquipNum;

	UPROPERTY(Meta = (WidgetBind))
		class UImage* WeaponImage;

	UPROPERTY(Meta = (WidgetBind))
		class UImage* UnEquipWeaponImage1;

	UPROPERTY(Meta = (WidgetBind))
		class UImage* UnEquipWeaponImage2;

	UPROPERTY(Meta = (WidgetBind))
		class UImage* UnEquipWeaponImage3;

	UPROPERTY(Meta = (WidgetBind))
		class UGridPanel* WeaponPanel;

protected:
	FTimerHandle CharacterNoticeHandle;

public:
	UFUNCTION()
	void SetHPbarPercentage(float Percentage);

	UFUNCTION()
	void SetSPbarPercentage(float Percentage);

	UFUNCTION()
	void EquipWeapon(EWeaponType WeaponType, class UTexture* WeaponIcon);

	UFUNCTION()
	void ShowAutoShootNotice(bool AutoShoot);

	UFUNCTION()
	void ShowCharacterNotice(FText str);
};
