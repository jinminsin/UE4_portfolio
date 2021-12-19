// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheZombiesCharacter.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Interaction = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction"));
	Interaction->SetupAttachment(RootComponent);
	Interaction->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	Interaction->SetBoxExtent(FVector(50.f, 50.f, 10.f));
	Interaction->SetCollisionProfileName("Interaction");
	Interaction->OnComponentBeginOverlap.AddDynamic(this, &AItem::BindInteractionCharacter);
	Interaction->OnComponentEndOverlap.AddDynamic(this, &AItem::UnBindInteractionCharacter);

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::BindInteractionCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Press F"), true, true, FLinearColor::Red, 5.0f);

	auto SweepCharacter = Cast<ATheZombiesCharacter>(OtherActor);

	if (SweepCharacter) {
		SweepCharacter->OnAddCurrentItem.Broadcast(this);
	}
}

void AItem::UnBindInteractionCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	auto SweepCharacter = Cast<ATheZombiesCharacter>(OtherActor);

	if (SweepCharacter) {
		SweepCharacter->OnRemoveCurrentItem.Broadcast(this);
	}
}

void AItem::SetInteractionCollision(bool bUseCollision) {
	if (bUseCollision)
		Interaction->SetCollisionProfileName("Interaction");
	else
		Interaction->SetCollisionProfileName("NoCollision");
}

void AItem::SetOwner(AActor* NewOwner) {
	Super::SetOwner(NewOwner);
	MyOwner = Cast<ATheZombiesCharacter>(NewOwner);
}

FItemData AItem::MakeItemData() {
	return FItemData(*DataTable->FindRow<FItemData>(*FString::FromInt(ItemRow), TEXT("")));
}