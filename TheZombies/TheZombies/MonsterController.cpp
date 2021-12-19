// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AMonsterController::AMonsterController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("CrowdFollowingComponent"))) {
	
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> ABT(TEXT("/Game/Resource/Character/Blueprints/AI/MonsterBT"));
	if (ABT.Succeeded())
	{
		BT = ABT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> ABB(TEXT("/Game/Resource/Character/Blueprints/AI/MonsterBB"));
	if (ABB.Succeeded())
	{
		BB = ABB.Object;
	}
}

void AMonsterController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (UseBlackboard(BB, Blackboard)) {	
		RunBehaviorTree(BT);
	}
}