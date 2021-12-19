// Fill out your copyright notice in the Description page of Project Settings.


#include "MapRules.h"
#include "NavigationSystem.h"
#include "Gun.h"
#include "GameIns.h"

AMapRules::AMapRules() {
}

void AMapRules::PostInitializeComponents() {
	Super::PostInitializeComponents();
	DropResourceMultipleCount = 100 + 10 * (Cast<UGameIns>(GetGameInstance())->GetLevelSelection());
}

void AMapRules::BeginPlay() {
	Super::BeginPlay();

	if (GetWorld()) {
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

		UE_LOG(LogTemp, Warning, TEXT("Enter"));

		if (NavSystem != nullptr) {

			UE_LOG(LogTemp, Warning, TEXT("Enter Complete"));

			for (int i = 0; i < 3; i++)
			{
				FNavLocation ResponLocation;
				UE_LOG(LogTemp, Warning, TEXT("Summon : %s"), *ResponLocation.Location.ToString());

				if (NavSystem->GetRandomPointInNavigableRadius(FVector(4300.f, 2400.f, 0.f), 2000.f, ResponLocation)) {
					GetWorld()->SpawnActor<AWeapon>(AGun::StaticClass(), ResponLocation.Location, FRotator::ZeroRotator);
					UE_LOG(LogTemp, Warning, TEXT("Summon Complete"));
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("Summon Failed : %s"), *ResponLocation.Location.ToString());
				}
			}
		}
	}
}

int32 AMapRules::GetDropResourceMultipleCount(int32 kinds) {
	return DropResourceMultipleCount;
}