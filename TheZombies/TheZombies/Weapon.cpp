// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ADataTable(TEXT("/Game/Resource/Data/KnifeDataTable"));
	if (ADataTable.Succeeded()) {
		DataTable = ADataTable.Object;
	}

	ItemRow = 1;
	FWeaponData* Data = DataTable->FindRow<FWeaponData>(*FString::FromInt(ItemRow), TEXT(""));

	Damage = Data->Damage;
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
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWeapon::Attack()
{
	
}

FItemData AWeapon::MakeItemData() {
	auto Data = FWeaponData(*DataTable->FindRow<FWeaponData>(*FString::FromInt(ItemRow), TEXT("")));
	Data.Durability = Durability;
	return Data;
}