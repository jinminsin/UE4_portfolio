// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterController.h"
#include "Monster.h"

UMonsterAttack::UMonsterAttack() {
	NodeName = TEXT("MeleeAttack");
	bCanAttack = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto Owner = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Owner) return EBTNodeResult::Failed;

	Owner->OnAttackMonatageEnded.AddDynamic(this, &UMonsterAttack::ReturnResult);
	bCanAttack = false;
	Owner->Attack(0);

	return EBTNodeResult::InProgress;
}

void UMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	auto Owner = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (bCanAttack) {
		Owner->OnAttackMonatageEnded.RemoveDynamic(this, &UMonsterAttack::ReturnResult);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UMonsterAttack::ReturnResult() {
	bCanAttack = true;
}