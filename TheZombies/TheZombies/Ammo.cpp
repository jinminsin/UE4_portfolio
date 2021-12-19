// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "Gun.h"
#include "Monster.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName("Bullet");
	Collision->SetBoxExtent(FVector(3.f, 0.5f, 0.5f));
	Collision->OnComponentHit.AddDynamic(this, &AAmmo::BulletHit);
	RootComponent = Collision;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletBody"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AMesh(TEXT("/Game/Resource/Weapons/Meshes/Ammunition/SM_Shell_545x39"));
	if (AMesh.Succeeded())
	{
		Body->SetStaticMesh(AMesh.Object);
		Body->SetRelativeLocationAndRotation(FVector(-0.5f, 0.f, 0.f), FRotator(0.f, -90.f, 0.f));
		Body->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));
		Body->SetCollisionProfileName("NoCollision");
	}
	Body->SetupAttachment(Collision);

	BlockEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BlockEffect"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AParticle(TEXT("/Game/Effects/ParticleSystems/Weapons/Rifle/Impacts/FireHit"));
	if (AParticle.Succeeded()) {
		BlockEffect->SetTemplate(AParticle.Object);
		BlockEffect->SetupAttachment(Collision);
		BlockEffect->bAutoActivate = false;
	}

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 1000.f;
	Movement->MaxSpeed = 1000.f;
	Movement->ProjectileGravityScale = 0.001f;
	Movement->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmo::BulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (!Cast<ACharacter>(OtherActor)) {
		//맞은 것이 움직이는 것이 아닐 경우
		BlockEffect->Activate(true);
	}
	else {
		Cast<AGun>(GetOwner())->DamageEnemy(Cast<AMonster>(OtherActor));
		Collision->SetCollisionProfileName("NoCollision");
		Body->SetVisibility(false);
	}

	SetLifeSpan(2.f);
}