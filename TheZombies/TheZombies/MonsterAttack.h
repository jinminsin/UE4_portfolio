// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MonsterAttack.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UMonsterAttack : public UBTTaskNode
{
	GENERATED_BODY()

	bool bCanAttack;

protected:
	UMonsterAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
		void ReturnResult();
};
