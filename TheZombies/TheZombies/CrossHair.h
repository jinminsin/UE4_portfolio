// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrossHair.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UCrossHair : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Meta = (WidgetBind))
		class UImage* CrosshairImage;

public:

};
