// Fill out your copyright notice in the Description page of Project Settings.


#include "GameIns.h"

void UGameIns::Init() {
	Super::Init();

	InventoryData.SetNum(60);
}

void UGameIns::SetMapSelection(int32 MapNum) {
	MapSelection = MapNum;
}

void UGameIns::SetLevelSelection(int32 Level) {
	LevelSelection = Level;
}

bool UGameIns::FarmingItemInInvetory(FItemData ItemData) {
	//�ߺ��Ǵ� �������� ã�´�.
	int32 BlankBlock = -1;

	for (int32 i = 0; i < InventoryData.Num(); i++) {
		if (ItemData.Name.CompareTo(InventoryData[i].Name) == 0) {
			if (InventoryData[i].CurrentCount + ItemData.CurrentCount < InventoryData[i].MaxCount) {
				InventoryData[i].CurrentCount += ItemData.CurrentCount;
				return true;
			}
			else {
				ItemData.CurrentCount -= (InventoryData[i].MaxCount - InventoryData[i].CurrentCount);
				InventoryData[i].CurrentCount = InventoryData[i].MaxCount;
			}
		}
		if (BlankBlock == -1 && InventoryData[i].Name.ToString().Compare(TEXT("")) == 0) BlankBlock = i;
	}

	//�ߺ��Ǵ� ĭ�� ��� ä��� ItemData�� CurrentCount�� ���� �ִٸ�, �ߺ��Ǵ� �������� ä��� ����.
	if (BlankBlock == -1) return false;

	InventoryData[BlankBlock] = ItemData;
	OnSetInventoryItem.Broadcast();
	return true;
	
}