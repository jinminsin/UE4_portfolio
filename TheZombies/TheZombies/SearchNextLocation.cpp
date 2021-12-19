// Fill out your copyright notice in the Description page of Project Settings.

#include "SearchNextLocation.h"
#include "NavigationSystem.h"
#include "MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"

USearchNextLocation::USearchNextLocation() {
    NodeName = TEXT("SearchNextLocation");
}

EBTNodeResult::Type USearchNextLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    auto Owner = OwnerComp.GetAIOwner()->GetPawn();
    if (!Owner) return EBTNodeResult::Failed;

    auto NavSystem = UNavigationSystemV1::GetNavigationSystem(Owner->GetWorld());
    if (!NavSystem) return EBTNodeResult::Failed;

    FNavLocation NextLocation;

    if (NavSystem->GetRandomPointInNavigableRadius(Owner->GetActorLocation(), 800.f, NextLocation)) {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("DestinationVector"), NextLocation.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}