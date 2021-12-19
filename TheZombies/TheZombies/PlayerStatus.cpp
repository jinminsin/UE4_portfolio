// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatus.h"
#include "Gun.h"
#include "GameIns.h"
#include "TheZombiesCharacter.h"

// Sets default values for this component's properties
UPlayerStatus::UPlayerStatus()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	Level = 1;

	MaxHP = 100.f;
	CurrentHP = 100.f;

	MaxSP = 100.f;
	CurrentSP = 100.f;

	Armor = 1.f;
}


// Called when the game starts
void UPlayerStatus::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerStatus::InitializeComponent() {
	Super::InitializeComponent();

	auto Owner = Cast<ATheZombiesCharacter>(GetOwner());
	Owner->OnAddCurrentItem.AddDynamic(this, &UPlayerStatus::AddFocusingItem);
	Owner->OnRemoveCurrentItem.AddDynamic(this, &UPlayerStatus::RemoveFocusingItem);
	Owner->OnAttackWeapon.AddDynamic(this, &UPlayerStatus::AttackCurrentWeapon);
}

// Called every frame
void UPlayerStatus::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerStatus::DoFarmingWeapon(){
	if (FocusingItem.Num()) {
		auto IfCurrentIsGun = Cast<AGun>(FocusingItem[0]);
		if (IfCurrentIsGun) {
			//총일 경우, if Main Rifle & Sub Rilfe != nullptr, 인벤토리
			if (MainWeapon != nullptr && SubWeapon != nullptr) {
				auto Inventory = Cast<UGameIns>(GetWorld()->GetGameInstance());
				if (Inventory->FarmingItemInInvetory(IfCurrentIsGun->MakeItemData())) {
					IfCurrentIsGun->Destroy();
				}
				else {
					OnShowCharacterNotice.Broadcast(FText::FromString(FString::Printf(TEXT("인벤토리가 가득 찼습니다."))));
				}
			}
			else {
				if (MainWeapon == nullptr) {
					MainWeapon = Cast<AGun>(FocusingItem[0]);
					OnEquipWeapon.Broadcast(EWeaponType::MainWeapon, IfCurrentIsGun->GetWeaponIcon());
				}
				else if (SubWeapon == nullptr) {
					SubWeapon = Cast<AGun>(FocusingItem[0]);
					OnEquipWeapon.Broadcast(EWeaponType::SubWeapon, IfCurrentIsGun->GetWeaponIcon());
				}
				//else 무기 전송, state 세팅
				//칼이나 폭발물 등의 보조무장과 달리 주무장인 메인과 서브는 줍는 즉시 바뀐다.
				CurWeapon = Cast<AWeapon>(FocusingItem[0]);
				OnDoFarmingCurrentWeapon.Broadcast(CurWeapon);
			}
		}
		else {
			//근접무기인 경우
			auto IfCurrentIsKnife = Cast<AWeapon>(FocusingItem[0]);
			if (Knife != nullptr) {
				if (CurWeapon == nullptr) {
					CurWeapon = Cast<AWeapon>(FocusingItem[0]);
					OnDoFarmingCurrentWeapon.Broadcast(CurWeapon);
				}

				OnEquipWeapon.Broadcast(EWeaponType::Knife, IfCurrentIsKnife->GetWeaponIcon());
			}
			else {
				auto Inventory = Cast<UGameIns>(GetWorld()->GetGameInstance());
				if (Inventory->FarmingItemInInvetory(IfCurrentIsKnife->MakeItemData())) {
					IfCurrentIsKnife->Destroy();
				}
				else {
					OnShowCharacterNotice.Broadcast(FText::FromString(FString::Printf(TEXT("인벤토리가 가득 찼습니다."))));
				}
			}

			//if CurrentWeapon == nullptr, CurrentWeapon = CurItem
			//else Equip Weapon not Set Current
		}

		//자원일 경우(탄창, 소모품 등)
		//그대로 인벤토리에 전송
		//TArray의 데이터 자료형을 변경할 필요가 있음.
	}
}

void UPlayerStatus::AddFocusingItem(AItem* CurItem) {
	FocusingItem.AddUnique(CurItem);
}

void UPlayerStatus::RemoveFocusingItem(AItem* CurItem) {
	if (FocusingItem.Contains(CurItem))
		FocusingItem.Remove(CurItem);
}

void UPlayerStatus::AttackCurrentWeapon() {
	if (CurWeapon) {
			CurWeapon->Attack();
	}
}

void UPlayerStatus::SetHP(float NewHP) {
	CurrentHP = NewHP;
	OnSetHP.Broadcast(CurrentHP / MaxHP);

	if (NewHP == 0) OnDecideCharacterDeath.Broadcast();
}

void UPlayerStatus::SetSP(float NewSP) {
	CurrentSP = NewSP;
	OnSetSP.Broadcast(CurrentSP / MaxSP);
}

void UPlayerStatus::TakeDamage(float Damage) {
	CurrentHP -= (Damage - Armor);

	if (CurrentHP < 0)
		CurrentHP = 0;

	SetHP(CurrentHP);
}

bool UPlayerStatus::GetCanRunning() {
	if (CurrentSP > 0) return true;

	return false;
}

void UPlayerStatus::CurrentWeaponToggle() {
	if (Cast<AGun>(CurWeapon)) {
		Cast<AGun>(CurWeapon)->ToggleAutoShoot();
	}
}