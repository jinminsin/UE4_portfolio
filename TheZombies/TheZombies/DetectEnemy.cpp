// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterController.h"
#include "Monster.h"
#include "TheZombiesCharacter.h"
#include "DrawDebugHelpers.h"

UDetectEnemy::UDetectEnemy() {
    NodeName = TEXT("DetectEnemy");
    Interval = 1.f;
}


void UDetectEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto Owner = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
    if (Owner == nullptr) return;

    TArray<FOverlapResult> SearchObject;
    FCollisionQueryParams params(NAME_None, false, Owner);
    bool Result = Owner->GetWorld()->OverlapMultiByChannel(SearchObject,
        Owner->GetActorLocation(),
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel7,
        FCollisionShape::MakeSphere(Owner->GetDetectRange()),
        params);


    if (Result) {
        for (auto obj : SearchObject) {
            ATheZombiesCharacter* Enemy = Cast<ATheZombiesCharacter>(obj.GetActor());

            if (Enemy && Enemy->IsPlayerControlled()) {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Enemy);
                DrawDebugSphere(Owner->GetWorld(), Owner->GetActorLocation(), Owner->GetDetectRange(), 32, FColor::Green, false, 0.2f);
                DrawDebugPoint(Owner->GetWorld(), Owner->GetActorLocation(), 50.f, FColor::Blue, false, 0.2f);
                DrawDebugLine(Owner->GetWorld(), Owner->GetActorLocation(), Enemy->GetActorLocation(), FColor::Green, false, 0.2f);
                return;
            }
        }
    }
    else {
        DrawDebugSphere(Owner->GetWorld(), Owner->GetActorLocation(), 400.f, 32, FColor::Red, false, 0.2f);
        DrawDebugPoint(Owner->GetWorld(), Owner->GetActorLocation(), 50.f, FColor::Emerald, false, 0.2f);
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
    }
}