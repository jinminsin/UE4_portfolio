// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnimInstance.h"
#include "TheZombiesCharacter.h"
#include "PlayerStatus.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"

UCharacterAnimInstance::UCharacterAnimInstance() {
	Speed = 0.f;
	IsJumping = false;
}

void UCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Owner = Cast<ATheZombiesCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Owner) {
		auto Velocity = Owner->GetVelocity();
		Speed = Velocity.Size2D();

		if (!Speed) Velocity = Owner->GetActorForwardVector();

		Velocity.Z = 0.f;
		Velocity.Normalize();

		auto CrossProductZ = FVector::CrossProduct(Owner->GetActorForwardVector(), Velocity).Z;
		auto Dot = FVector::DotProduct(Owner->GetActorForwardVector(), Velocity);

		if (CrossProductZ < 0)
			Degree = -FMath::RadiansToDegrees(FMath::Acos(Dot));
		else
			Degree = FMath::RadiansToDegrees(FMath::Acos(Dot));

		IsJumping = Owner->GetCharacterMovement()->IsFalling();

		FRotator OwnerRot = Owner->GetController()->GetControlRotation();
		OwnerRot.Normalize();

		CharacterCurrentPitch = OwnerRot.Pitch;\
		
		CurState = Owner->GetStateCharacter();
		LeftHandIKVector = Owner->GetCurrentLeftHandIKVector();
		RightHandIKVector = Owner->GetCurrentRightHandIKVector();
	}
}

void UCharacterAnimInstance::AnimNotify_Death() {
	Owner->OnDunGeonEnd.Broadcast();
}