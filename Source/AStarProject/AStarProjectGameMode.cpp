// Copyright Epic Games, Inc. All Rights Reserved.

#include "AStarProjectGameMode.h"
#include "AStarProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAStarProjectGameMode::AAStarProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
