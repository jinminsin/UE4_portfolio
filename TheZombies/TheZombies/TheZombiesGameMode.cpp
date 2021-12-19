// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheZombiesGameMode.h"
#include "TheZombiesCharacter.h"
#include "CurrentUseWidget.h"
#include "UObject/ConstructorHelpers.h"

ATheZombiesGameMode::ATheZombiesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Resource/Character/Blueprints/Bryce/Bryce"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = ACurrentUseWidget::StaticClass();
}
