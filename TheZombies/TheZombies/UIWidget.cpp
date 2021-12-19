// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidget.h"
#include "Components/GridPanel.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UUIWidget::SetHPbarPercentage(float Percentage) {
	HPbar->SetPercent(Percentage);	
	HP->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Percentage * 100)));
}

void UUIWidget::SetSPbarPercentage(float Percentage) {
	SPbar->SetPercent(Percentage);
	SP->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Percentage * 100)));
}

void UUIWidget::EquipWeapon(EWeaponType WeaponType, class UTexture* WeaponIcon) {
	switch (WeaponType) {
	case EWeaponType::MainWeapon:
		WeaponImage->SetBrushResourceObject(WeaponIcon);
		WeaponPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case EWeaponType::SubWeapon:
		UnEquipWeaponImage1->SetBrushResourceObject(WeaponImage->Brush.GetResourceObject());
		UnEquipWeaponImage1->SetVisibility(ESlateVisibility::Visible);

		WeaponImage->SetBrushResourceObject(WeaponIcon);
		break;
	case EWeaponType::Knife:
		UnEquipWeaponImage2->SetBrushResourceObject(WeaponIcon);
		UnEquipWeaponImage2->SetVisibility(ESlateVisibility::Visible);
		break;
	case EWeaponType::Generade:
		UnEquipWeaponImage3->SetBrushResourceObject(WeaponIcon);
		UnEquipWeaponImage3->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

void UUIWidget::ShowAutoShootNotice(bool AutoShoot) {
	FString str = FString::Printf(TEXT("사격 모드 변경 : %s"), AutoShoot ? TEXT("자동") : TEXT("단발"));
	ShowCharacterNotice(FText::FromString(str));
}

void UUIWidget::ShowCharacterNotice(FText str) {
	GetWorld()->GetTimerManager().ClearTimer(CharacterNoticeHandle);

	CharacterNotice->SetText(str);
	CharacterNotice->SetRenderOpacity(1);

	GetWorld()->GetTimerManager().SetTimer(CharacterNoticeHandle, FTimerDelegate::CreateLambda([&]() {
		CharacterNotice->SetRenderOpacity(CharacterNotice->GetRenderOpacity() - 0.1);

		if (CharacterNotice->GetRenderOpacity() <= 0) GetWorld()->GetTimerManager().ClearTimer(CharacterNoticeHandle);
		}), 0.5f, true);
}