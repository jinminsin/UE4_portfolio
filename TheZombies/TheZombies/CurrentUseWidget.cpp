// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrentUseWidget.h"
#include "UIWidget.h"
#include "TheZombiesCharacter.h"
#include "PlayerStatus.h"
#include "CrossHair.h"
#include "EquipmentAndInventoryUIWidget.h"
#include "Blueprint/UserWidget.h"

ACurrentUseWidget::ACurrentUseWidget() {
	static ConstructorHelpers::FClassFinder<UUserWidget> BaseCrosshairWidget(TEXT("/Game/Resource/Character/UI/CrosshairWidget"));
	if (BaseCrosshairWidget.Succeeded()) {
		CrossHairClass = BaseCrosshairWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> BaseUIWidget(TEXT("/Game/Resource/Character/UI/UIWidget"));
	if (BaseUIWidget.Succeeded()) {
		StateUIClass = BaseUIWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> DunGeonEndUIWidget(TEXT("/Game/Resource/Character/UI/DunGeonEndWidget"));
	if (DunGeonEndUIWidget.Succeeded()) {
		DunGeonEndUIClass = DunGeonEndUIWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> EquipmentAndInventoryUIWidget(TEXT("/Game/Resource/Character/UI/EquipmentAndInventoryUIWidget"));
	if (EquipmentAndInventoryUIWidget.Succeeded()) {
		EquipmentAndInventoryUIClass = EquipmentAndInventoryUIWidget.Class;
	}
}

void ACurrentUseWidget::BeginPlay() {
	Super::BeginPlay();
}

void ACurrentUseWidget::PostInitializeComponents() {
	Super::PostInitializeComponents();
	CrossHair = CreateWidget(GetWorld(), CrossHairClass);
	StateUI = CreateWidget(GetWorld(), StateUIClass);
	DunGeonEndUI = CreateWidget(GetWorld(), DunGeonEndUIClass);
	EquipmentAndInventoryUI = CreateWidget(GetWorld(), EquipmentAndInventoryUIClass);
}

void ACurrentUseWidget::ShowUIWidget(class ATheZombiesCharacter* Player) {
	CrossHair->AddToViewport();

	auto PlayerStatus = Player->GetPlayerStatus();

	PlayerStatus->OnSetHP.AddDynamic(Cast<UUIWidget>(StateUI), &UUIWidget::SetHPbarPercentage);
	PlayerStatus->OnSetSP.AddDynamic(Cast<UUIWidget>(StateUI), &UUIWidget::SetSPbarPercentage);
	PlayerStatus->OnEquipWeapon.AddDynamic(Cast<UUIWidget>(StateUI), &UUIWidget::EquipWeapon);
	PlayerStatus->OnShowCharacterNotice.AddDynamic(Cast<UUIWidget>(StateUI), &UUIWidget::ShowCharacterNotice);
	Player->OnChangeAutoShoot.AddDynamic(Cast<UUIWidget>(StateUI), &UUIWidget::ShowAutoShootNotice);
	StateUI->AddToViewport();

	PlayerStatus->OnEquipWeapon.AddDynamic(Cast<UEquipmentAndInventoryUIWidget>(EquipmentAndInventoryUI), &UEquipmentAndInventoryUIWidget::EquipWeapon);
	Player->OnToggleEquipmentAndInventory.AddDynamic(Cast<UEquipmentAndInventoryUIWidget>(EquipmentAndInventoryUI), &UEquipmentAndInventoryUIWidget::TogglePanel);
	EquipmentAndInventoryUI->AddToViewport();

	Player->OnDunGeonEnd.AddDynamic(this, &ACurrentUseWidget::ShowDunGeonEndWidget);
}

void ACurrentUseWidget::ShowDunGeonEndWidget() {
	StateUI->RemoveFromViewport();
	CrossHair->RemoveFromViewport();
	DunGeonEndUI->AddToViewport();

	PlayerOwner->SetInputMode(FInputModeUIOnly());
}