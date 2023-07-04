// Copyright Epic Games, Inc. All Rights Reserved.

#include "IA_ZombiesGameMode.h"
#include "IA_ZombiesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIA_ZombiesGameMode::AIA_ZombiesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
