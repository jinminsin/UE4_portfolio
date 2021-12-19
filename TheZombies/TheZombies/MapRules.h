// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MapRules.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API AMapRules : public ALevelScriptActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Resource, meta = (AllowPrivateAccess = "true"))
		int32 DropResourceMultipleCount;
public:
	AMapRules();

	int32 GetDropResourceMultipleCount(int32 kinds);
	
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
};
