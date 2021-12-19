// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API AMonsterController : public AAIController
{
	GENERATED_BODY()

protected:
    AMonsterController(const FObjectInitializer& ObjectInitializer);

    virtual void OnPossess(APawn* InPawn) override;

private:
    UPROPERTY()
        class UBehaviorTree* BT;
    UPROPERTY()
        class UBlackboardData* BB;

};
