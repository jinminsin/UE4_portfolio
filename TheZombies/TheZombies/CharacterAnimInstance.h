// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEZOMBIES_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UCharacterAnimInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Degree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CharacterCurrentPitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector LeftHandIKVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector RightHandIKVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EStateCharacter CurState;

	UFUNCTION()
		void AnimNotify_Death();

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	class ATheZombiesCharacter* Owner;
};
