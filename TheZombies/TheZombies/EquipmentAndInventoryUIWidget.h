// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentAndInventoryUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UEquipmentAndInventoryUIWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		class UImage* MainWeaponImage;

	UPROPERTY(meta = (BindWidget))
		class UImage* SubWeaponImage;

	UPROPERTY(meta = (BindWidget))
		class UImage* KnifeImage;

	UPROPERTY(meta = (BindWidget))
		class UImage* GeneradeImage;

	UPROPERTY(meta = (BindWidget))
		class UGridPanel* Equipment;

	UPROPERTY(meta = (BindWidget))
		class UGridPanel* Inventory;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* InventoryList;

	UPROPERTY()
		TSubclassOf<UUserWidget> ItemSlotClass;

protected:
	UEquipmentAndInventoryUIWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
		void SetInventoryItem();

	UFUNCTION()
		void TogglePanel(int32 TogglePanel);

	UFUNCTION()
		void EquipWeapon(EWeaponType WeaponType, class UTexture* WeaponIcon);
	
};
