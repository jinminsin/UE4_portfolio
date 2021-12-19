// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "MonsterController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Zombie"));

	MaxHP = 50.f;
	CurrentHP = MaxHP;
	Armor = 5.f;
	Damage = 5.f;
	AttackRange = 50.f;
	DetectRange = 400.f;
	rarity = 0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxWalkSpeed = 45.f;
	GetCharacterMovement()->MaxSwimSpeed = 22.5f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 22.5f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.f, 0.0f);
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> Amesh(TEXT("/Game/Resource/Character/Zombie_M/zombie"));
	if (Amesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(Amesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(.0f, .0f, -89.f), FRotator(.0f, -90.0f, .0f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnAnim(TEXT("/Game/Resource/Character/Blueprints/Zombie_M/ZombieAnimation"));
	if (AnAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnAnim.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMontage(TEXT("/Game/Resource/Character/Blueprints/Zombie_M/AttackMontage"));
	if (AMontage.Succeeded())
	{
		AttackMontage = AMontage.Object;
	}

	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(GetCapsuleComponent());

	static ConstructorHelpers::FClassFinder<UUserWidget> AHealthBarWidget(TEXT("/Game/Resource/Character/UI/MonsterHealthBar"));
	if (AHealthBarWidget.Succeeded()) {
		HealthBarComponent->SetWidgetClass(AHealthBarWidget.Class);
		HealthBarComponent->SetDrawSize(FVector2D(100.f, 5.f));
	}

	HealthBarComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	HealthBarComponent->SetVisibility(true);

	bIsAttacking = false;

	AIControllerClass = AMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMonster::PostInitializeComponents() {
	Super::PostInitializeComponents();
	auto AnimIns = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	AnimIns->OnMontageEnded.AddDynamic(this, &AMonster::AttackMontageEnded);
	AnimIns->OnAttackHitCheck.AddDynamic(this, &AMonster::AttackHit);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerEyes = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	HealthBarComponent->SetWorldRotation((PlayerEyes - HealthBarComponent->GetComponentLocation()).Rotation());

}

void AMonster::AttackMontageEnded(class UAnimMontage* Montage, bool bInterrupted) {
	if (Montage == AttackMontage) {
		OnAttackMonatageEnded.Broadcast();
		bIsAttacking = false;
	}
}

void AMonster::Attack(int32 AttackKinds) {
	switch (AttackKinds) {
		case 0:
			if (!bIsAttacking) {
				bIsAttacking = true;
				PlayAnimMontage(AttackMontage);
			}
			break;
		default:
			break;
	}

}

void AMonster::AttackHit() {
	FHitResult OutHit;
	FCollisionQueryParams params(NAME_None, false, this);

	auto Range = AttackRange + GetCapsuleComponent()->GetScaledCapsuleRadius();

	bool bResult = GetWorld()->SweepSingleByChannel(OutHit,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * Range,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7,
		FCollisionShape::MakeSphere(50.f),
		params);


	if (bResult) {
		DrawDebugCapsule(GetWorld(), GetActorLocation() + (GetActorForwardVector() * Range) / 2, Range/2 + 50.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector() * Range).ToQuat(), FColor::Green, false, 5.f);
		UGameplayStatics::ApplyDamage(OutHit.GetActor(), Damage, GetController(), this, UDamageType::StaticClass());
	}
	else {
		DrawDebugCapsule(GetWorld(), GetActorLocation() + (GetActorForwardVector() * Range) / 2, Range / 2 + 50.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector() * Range).ToQuat(), FColor::Red, false, 5.f);
	}
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	CurrentHP -= DamageAmount;

	if (CurrentHP <= 0) {
		CurrentHP = 0;
		CharacterDeath();
	}

	Cast<UHealthBarWidget>(HealthBarComponent->GetWidget())->SetHPbarPercentage(CurrentHP / MaxHP);

	return Damage;
}

void AMonster::CharacterDeath() {
	GetController()->UnPossess();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CorpseZombie"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	SetLifeSpan(5.f);
}