// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DetectEnemyInSightRange.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UDetectEnemyInSightRange : public UBTDecorator
{
	GENERATED_BODY()

protected:
	UDetectEnemyInSightRange();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
