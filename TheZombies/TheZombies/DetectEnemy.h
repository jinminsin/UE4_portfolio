// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DetectEnemy.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UDetectEnemy : public UBTService
{
	GENERATED_BODY()
	
public:
	UDetectEnemy();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
