// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheZombiesCharacter.h"
#include "PlayerStatus.h"
#include "Weapon.h"
#include "Gun.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "CurrentUseWidget.h"
#include "GameFramework/PlayerController.h"

ATheZombiesCharacter::ATheZombiesCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 87.0f);
	GetCapsuleComponent()->SetCollisionProfileName("Character");
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AMesh(TEXT("/Game/Resource/Character/Bryce/Ch42_nonPBR"));
	if (AMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(AMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(.0f, .0f, -92.0f), FRotator(.0f, -90.0f, .0f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnAnim(TEXT("/Game/Resource/Character/Blueprints/Bryce/BryceAnimation"));
	if (AnAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnAnim.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AHitReactMontage(TEXT("/Game/Resource/Character/Blueprints/Bryce/HitReactMontage"));
	if (AHitReactMontage.Succeeded())
	{
		HitReactMontage = AHitReactMontage.Object;
	}

	/*static ConstructorHelpers::FObjectFinder<UAnimMontage> AFireMontage(TEXT("/Game/Resource/Character/Blueprints/Bryce/FireMontage"));
	if (AFireMontage.Succeeded())
	{
		FireMontage = AFireMontage.Object;
	}*/

	bUseControllerRotationPitch	= false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MaxSwimSpeed = 150.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0.0f, 30.f, 90.f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	PlayerStatus = CreateDefaultSubobject<UPlayerStatus>(TEXT("Status"));

	CurrentState = EStateCharacter::NoWeapon;

	bBurstAttack = false;

	RecoilRange = 30.f;
}

void ATheZombiesCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATheZombiesCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ATheZombiesCharacter::StopAttack);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ATheZombiesCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ATheZombiesCharacter::Walk);
	PlayerInputComponent->BindAction("ToggleShootingMode", IE_Pressed, this, &ATheZombiesCharacter::ToggleShootingMode);
	PlayerInputComponent->BindAction("InterAction", IE_Pressed, this, &ATheZombiesCharacter::InterAction);
	PlayerInputComponent->BindAction("Equipment", IE_Pressed, this, &ATheZombiesCharacter::ToggleEquipment);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ATheZombiesCharacter::ToggleInventory);
	PlayerInputComponent->BindAction("EquipmentAndInventory", IE_Pressed, this, &ATheZombiesCharacter::ToggleEquipmentAndInventory);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATheZombiesCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATheZombiesCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ATheZombiesCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();

	PlayerStatus->OnDoFarmingCurrentWeapon.AddDynamic(this, &ATheZombiesCharacter::DrawWeapon);
	PlayerStatus->OnDecideCharacterDeath.AddDynamic(this, &ATheZombiesCharacter::CharacterDeath);
}

void ATheZombiesCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	if (IsPlayerControlled()) {
		auto PC = Cast<APlayerController>(NewController);
		if (PC) {
			auto UIWidget = Cast<ACurrentUseWidget>(PC->GetHUD());

			if (UIWidget) {
				UIWidget->ShowUIWidget(this);
			}
		}
	}
}

void ATheZombiesCharacter::MoveForward(float Value)
{	
	MoveInterpolationVector.X = Value;

	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value / MoveInterpolationVector.Size());
	}
}

void ATheZombiesCharacter::MoveRight(float Value)
{
	MoveInterpolationVector.Y = Value;

	if ( (Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value / MoveInterpolationVector.Size());
	}
}

void ATheZombiesCharacter::Run() {
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxSwimSpeed = 300.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 300.f;
}

void ATheZombiesCharacter::Walk() {
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MaxSwimSpeed = 150.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.f;
}

void ATheZombiesCharacter::InterAction() {
	PlayerStatus->DoFarmingWeapon();
}

void ATheZombiesCharacter::DrawWeapon(AWeapon* CurWeapon) {
	CurWeapon->SetOwner(this);
	CurWeapon->GetBody()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
	CurWeapon->SetActorRelativeTransform(CurWeapon->GetRightHandSocketTransform());
	CurWeapon->SetInteractionCollision(false);

	if (Cast<AGun>(CurWeapon) != nullptr) {
		CurrentLeftHandIKVector = Cast<AGun>(CurWeapon)->GetLeftHandIKVector();
		CurrentRightHandIKVector = Cast<AGun>(CurWeapon)->GetRightHandIKVector();
		CurrentState = EStateCharacter::Rifle;
	}
	else {
		CurrentState = EStateCharacter::Knife;
	}
}

void ATheZombiesCharacter::Attack() {
	bBurstAttack = true;
	OnAttackWeapon.Broadcast();
}

void ATheZombiesCharacter::StopAttack() {
	bBurstAttack = false;
}

FVector ATheZombiesCharacter::GetAimVector(float Range) {
	FHitResult result;
	FVector StartVector = CameraBoom->GetComponentLocation();
	FVector EndVector = StartVector + CameraBoom->GetTargetRotation().Quaternion().GetForwardVector() * Range
		+ GetActorRightVector() * FMath::FRandRange(-RecoilRange, RecoilRange) + GetActorUpVector() * FMath::FRandRange(-RecoilRange, RecoilRange);
	FCollisionQueryParams params(NAME_None, false, this);

	DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Green, false, 5.f);

	if (GetWorld()->LineTraceSingleByChannel(result, StartVector, EndVector, ECollisionChannel::ECC_GameTraceChannel6, params)) {
		DrawDebugBox(GetWorld(), result.ImpactPoint, FVector(5.f, 5.f, 5.f), FColor::Red, false, 5.f);
		return result.ImpactPoint;
	}
	else {
		DrawDebugBox(GetWorld(), EndVector, FVector(5.f, 5.f, 5.f), FColor::Red, false, 5.f);
		return EndVector;
	}
}

float ATheZombiesCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	if (CurrentState != EStateCharacter::Death) {
		PlayerStatus->TakeDamage(DamageAmount);
		PlayAnimMontage(HitReactMontage, 1.f, FName(*FString::Printf(TEXT("%d"), FMath::RandRange(1, 4))));
	}

	return DamageAmount;
}

void ATheZombiesCharacter::CharacterDeath() {
	GetCapsuleComponent()->SetCollisionProfileName("Corpse");
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	bUseControllerRotationYaw = false;
	CurrentState = EStateCharacter::Death;
}

void ATheZombiesCharacter::ToggleShootingMode() {
	if (!bBurstAttack)
		PlayerStatus->CurrentWeaponToggle();
}

void ATheZombiesCharacter::ToggleInventory() {
	OnToggleEquipmentAndInventory.Broadcast(0);
}
void ATheZombiesCharacter::ToggleEquipment() {
	OnToggleEquipmentAndInventory.Broadcast(1);
}
void ATheZombiesCharacter::ToggleEquipmentAndInventory() {
	OnToggleEquipmentAndInventory.Broadcast(2);
}