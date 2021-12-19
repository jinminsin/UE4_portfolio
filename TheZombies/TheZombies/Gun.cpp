// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Monster.h"
#include "Ammo.h"
#include "TheZombiesCharacter.h"
#include "Sound/SoundCue.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AGun::AGun() {
	static ConstructorHelpers::FObjectFinder<UDataTable> ADataTable(TEXT("/Game/Resource/Data/GunDataTable"));
	if (ADataTable.Succeeded()) {
		DataTable = ADataTable.Object;
	}

	ItemRow = FMath::RandRange(1,2);
	FGunData* Data = DataTable->FindRow<FGunData>(*FString::FromInt(ItemRow), TEXT(""));
	
	Damage = Data->Damage;
	Recoil = Data->Recoil;

	RPM = Data->RPM;
	Range = Data->Range;

	Icon = Data->Icon;
	WeaponIcon = Data->WeaponIcon;

	Body->SetSkeletalMesh(Data->Body);
	Body->SetRelativeTransform(Data->BodyTransform);
	Body->SetCollisionProfileName("Weapon");

	Name = Data->Name;
	FlavorText = Data->FlavorText;
	Durability = Data->Durability;
	CurrentCount = Data->CurrentCount;
	MaxCount = Data->MaxCount;
	AttackMontage = Data->AttackMontage;

	MuzzleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleEffect"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> AParticle(TEXT("/Game/Effects/ParticleSystems/Weapons/Rifle/Muzzle/Fire"));
	if (AParticle.Succeeded()) {
		MuzzleEffect->SetTemplate(AParticle.Object);
		MuzzleEffect->SetupAttachment(Body, TEXT("Muzzle"));
		MuzzleEffect->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> AFireSound(TEXT("/Game/Resource/Sounds2/GunShot"));
	if (AFireSound.Succeeded()) {
		FireSound = AFireSound.Object;
	}

	AutoShoot = true;
	IsFiring = false;
	IsReFiring = false;
}	

void AGun::Attack() {
	if (!IsFiring && !IsReFiring) {
		IsFiring = true;
		Fire();
	}
}

void AGun::CanFire() {
	IsFiring = false;
	IsReFiring = false;
}

void AGun::Fire() {
	if (MyOwner) {
		MuzzleEffect->Activate(true);
		FVector AimVector = MyOwner->GetAimVector(Range);
		FTransform SpawnTransform = FTransform((AimVector - Body->GetSocketLocation("Muzzle")).Rotation(), Body->GetSocketLocation("Muzzle"));

		auto ShootAmmo = GetWorld()->SpawnActorDeferred<AAmmo>(AAmmo::StaticClass(), SpawnTransform, Cast<AActor>(this));

		ShootAmmo->GetCollision()->IgnoreActorWhenMoving(MyOwner, true);
		ShootAmmo->FinishSpawning(SpawnTransform);
		MyOwner->PlayAnimMontage(AttackMontage);
		MyOwner->AddControllerPitchInput(-Recoil);

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());

		GetWorldTimerManager().SetTimer(FireHandle, FTimerDelegate::CreateLambda([&]() {
			MuzzleEffect->Deactivate();

			if (AutoShoot) {
				if (MyOwner->CanBurstAttack()) {
					IsReFiring = true;
					Fire();
				}
				else
					CanFire();
			}
			else {
				MyOwner->StopAttack();
				CanFire();
			}
			}), (float)60 / RPM, false);
	}
}

void AGun::DamageEnemy(class AMonster* Enemy) {
	UGameplayStatics::ApplyDamage(Enemy, Damage, MyOwner->GetController(), this, UDamageType::StaticClass());
}

void AGun::ToggleAutoShoot() {
	AutoShoot = !AutoShoot;
	MyOwner->OnChangeAutoShoot.Broadcast(AutoShoot);
}