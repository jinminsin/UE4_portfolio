// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Monster.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"

UMonsterAnimInstance::UMonsterAnimInstance() {
	Speed = 0.f;
	IsJumping = false;
}

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Owner = Cast<AMonster>(TryGetPawnOwner());
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Owner) {
		Speed = Owner->GetVelocity().Size2D();
		IsJumping = Owner->GetCharacterMovement()->IsFalling();
		IsAlive = Owner->GetIsAlive();
	}
}

void UMonsterAnimInstance::AnimNotify_AttackHitCheck() {
	OnAttackHitCheck.Broadcast();
}