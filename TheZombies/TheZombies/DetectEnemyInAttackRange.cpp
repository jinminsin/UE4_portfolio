// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectEnemyInAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterController.h"
#include "Monster.h"
#include "TheZombiesCharacter.h"
#include "Components/CapsuleComponent.h"


UDetectEnemyInAttackRange::UDetectEnemyInAttackRange() {
	NodeName = TEXT("DetectEnemyInAttackRange");
}

bool UDetectEnemyInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
    auto Owner = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
    auto Enemy = Cast<ATheZombiesCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

    if (Owner != nullptr && Enemy != nullptr)
    {
        if (Owner->GetIsAttacking())
            return true;

        return (Owner->GetDistanceTo(Enemy) <= Owner->GetAttackRange() + Owner->GetCapsuleComponent()->GetScaledCapsuleRadius() + Enemy->GetCapsuleComponent()->GetScaledCapsuleRadius());
    }

    return false;
}
