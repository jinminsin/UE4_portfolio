// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackHitCheck);

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UMonsterAnimInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsAlive;

	UFUNCTION()
		void AnimNotify_AttackHitCheck();

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	class AMonster* Owner;
	FOnAttackHitCheck OnAttackHitCheck;
};
