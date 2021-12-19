// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAndInventoryUIWidget.h"
#include "GameIns.h"
#include "ItemSlot.h"
#include "ItemTable.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

UEquipmentAndInventoryUIWidget::UEquipmentAndInventoryUIWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	
	static ConstructorHelpers::FClassFinder<UUserWidget> AItemSlotClass(TEXT("/Game/Resource/Character/UI/ItemSlot"));
	if (AItemSlotClass.Succeeded()) {
		ItemSlotClass = AItemSlotClass.Class;
	}
}

void UEquipmentAndInventoryUIWidget::NativeConstruct() {
	Super::NativeConstruct();

	auto instance = Cast<UGameIns>(GetGameInstance());
	instance->OnSetInventoryItem.AddDynamic(this, &UEquipmentAndInventoryUIWidget::SetInventoryItem);

	SetInventoryItem();
}

void UEquipmentAndInventoryUIWidget::SetInventoryItem() {
	InventoryList->ClearChildren();

	auto instance = Cast<UGameIns>(GetGameInstance());
	auto ItemData = instance->GetInventoryData();

	for (int32 i = 0; i < ItemData.Num(); i++) {
		FItemData Data = ItemData[i];
		UItemSlot* Item = Cast<UItemSlot>(CreateWidget(this, ItemSlotClass));
		if (Data.Name.ToString().Compare(TEXT(""))) {
			Item->SetItemIcon(Data.Icon);
			Item->SetCurrentCount(Data.CurrentCount);
		}
		InventoryList->AddChildToUniformGrid(Item, i / 5, i % 5);
	}
}

void UEquipmentAndInventoryUIWidget::TogglePanel(int32 TogglePanel) {
	// TogglePanel == 0 (Inventory), == 1(Equipment), == 2(All)
	if (TogglePanel == 0) {
		if (Inventory->GetVisibility() == ESlateVisibility::Collapsed) {
			SetInventoryItem();
			Inventory->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
			Inventory->SetVisibility(ESlateVisibility::Collapsed);
	}
	else if (TogglePanel == 1) {
		if (Equipment->GetVisibility() == ESlateVisibility::Collapsed)
			Equipment->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		else
			Equipment->SetVisibility(ESlateVisibility::Collapsed);
	}
	else {
		if (Equipment->GetVisibility() == ESlateVisibility::Collapsed && Inventory->GetVisibility() == ESlateVisibility::Collapsed)
		{
			SetInventoryItem();
			Inventory->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Equipment->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else {
			Inventory->SetVisibility(ESlateVisibility::Collapsed);
			Equipment->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UEquipmentAndInventoryUIWidget::EquipWeapon(EWeaponType WeaponType, class UTexture* WeaponIcon) {
	switch (WeaponType) {
	case EWeaponType::MainWeapon:
		MainWeaponImage->SetBrushResourceObject(WeaponIcon);
		MainWeaponImage->SetVisibility(ESlateVisibility::Visible);
		break;
	case EWeaponType::SubWeapon:
		SubWeaponImage->SetBrushResourceObject(WeaponIcon);
		SubWeaponImage->SetVisibility(ESlateVisibility::Visible);
		break;
	case EWeaponType::Knife:
		KnifeImage->SetBrushResourceObject(WeaponIcon);
		KnifeImage->SetVisibility(ESlateVisibility::Visible);
		break;
	case EWeaponType::Generade:
		GeneradeImage->SetBrushResourceObject(WeaponIcon);
		GeneradeImage->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}