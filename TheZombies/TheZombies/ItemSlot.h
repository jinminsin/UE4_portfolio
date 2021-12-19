// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
		class UButton* ItemBtn;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentCount;

public:
	void SetItemIcon(class UTexture* Icon);
	void SetCurrentCount(int32 Count);
};
