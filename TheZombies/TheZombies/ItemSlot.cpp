// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UItemSlot::SetItemIcon(class UTexture* Icon) {
	ItemIcon->SetBrushResourceObject(Icon);
	ItemIcon->SetVisibility(ESlateVisibility::Visible);
}

void UItemSlot::SetCurrentCount(int32 Count) {
	CurrentCount->SetText(FText::FromString(FString::Printf(TEXT("x %d"), Count)));
	CurrentCount->SetVisibility(ESlateVisibility::Visible);
}
