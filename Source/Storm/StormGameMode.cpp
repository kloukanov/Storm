// Copyright Epic Games, Inc. All Rights Reserved.

#include "StormGameMode.h"
#include "StormCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStormGameMode::AStormGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
