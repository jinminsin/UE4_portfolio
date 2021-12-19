// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectEnemyInSightRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterController.h"
#include "Monster.h"
#include "TheZombiesCharacter.h"
#include "Components/CapsuleComponent.h"

UDetectEnemyInSightRange::UDetectEnemyInSightRange() {
	NodeName = TEXT("DetectEnemyInSightRange");
}

bool UDetectEnemyInSightRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
    auto Owner = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
    auto Enemy = Cast<ATheZombiesCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

    if (Owner != nullptr && Enemy != nullptr)
    {
        if (Owner->GetIsAttacking())
            return true;

        FVector ToTargetSightVector = Enemy->GetActorLocation() - Owner->GetActorLocation();
        ToTargetSightVector.Normalize();
        return (FVector::DotProduct(Owner->GetActorForwardVector(), ToTargetSightVector) > cos(FMath::DegreesToRadians(15)));
    }

    return false;
}
