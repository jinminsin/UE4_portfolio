// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CurrentUseWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API ACurrentUseWidget : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
		TSubclassOf<UUserWidget> CrossHairClass;

	UPROPERTY()
		TSubclassOf<UUserWidget> StateUIClass;

	UPROPERTY()
		TSubclassOf<UUserWidget> DunGeonEndUIClass;

	UPROPERTY()
		TSubclassOf<UUserWidget> EquipmentAndInventoryUIClass;

	UPROPERTY()
		class UUserWidget* CrossHair;

	UPROPERTY()
		class UUserWidget* StateUI;

	UPROPERTY()
		class UUserWidget* DunGeonEndUI;

	UPROPERTY()
		class UUserWidget* EquipmentAndInventoryUI;
		
public:
	ACurrentUseWidget();
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void ShowUIWidget(class ATheZombiesCharacter* Player);

	UFUNCTION()
		void ShowDunGeonEndWidget();
};
