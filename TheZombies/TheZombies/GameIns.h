// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemTable.h"
#include "Engine/GameInstance.h"
#include "GameIns.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSetInventoryItem);

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UGameIns : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Selection, meta = (AllowPrivateAccess = "true"))
		int32 MapSelection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Selection, meta = (AllowPrivateAccess = "true"))
		int32 LevelSelection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
		TArray<FItemData> InventoryData;

protected:
	virtual void Init() override;

public:
	FORCEINLINE TArray<FItemData> GetInventoryData() const { return InventoryData; }
	FORCEINLINE int32 GetMapSelection() const { return MapSelection; }
	FORCEINLINE int32 GetLevelSelection() const { return LevelSelection; }

	FOnSetInventoryItem OnSetInventoryItem;

	void SetLevelSelection(int32 Level);
	void SetMapSelection(int32 MapNum);
	bool FarmingItemInInvetory(FItemData ItemData);
};
