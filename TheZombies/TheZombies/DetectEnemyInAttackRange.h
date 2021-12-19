// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DetectEnemyInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UDetectEnemyInAttackRange : public UBTDecorator
{
	GENERATED_BODY()

protected:
	UDetectEnemyInAttackRange();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
