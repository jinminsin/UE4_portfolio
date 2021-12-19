// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnumClass.generated.h"

UENUM(BlueprintType)
enum class EStateCharacter :uint8 {
	NoWeapon		UMETA(Displayname = "NoWeapon"),
	Rifle			UMETA(Displayname = "Rifle"),
	Knife			UMETA(Displayname = "Knife"),
	Generade		UMETA(Displayname = "Generade"),
	Death			UMETA(DIsplayname = "Death"),
};

UENUM(BlueprintType)
enum class EWeaponType :uint8 {
	MainWeapon		UMETA(Displayname = "MainWeapon"),
	SubWeapon		UMETA(Displayname = "SubWeapon"),
	Knife			UMETA(Displayname = "Knife"),
	Generade		UMETA(Displayname = "Generade"),
};