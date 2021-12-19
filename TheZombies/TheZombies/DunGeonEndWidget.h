// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DunGeonEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UDunGeonEndWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (WidgetBind))
		class UTextBlock* Text;
};
