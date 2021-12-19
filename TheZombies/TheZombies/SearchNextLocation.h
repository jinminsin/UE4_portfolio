// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SearchNextLocation.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API USearchNextLocation : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	USearchNextLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
