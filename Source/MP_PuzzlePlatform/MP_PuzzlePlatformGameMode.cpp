// Copyright Epic Games, Inc. All Rights Reserved.

#include "MP_PuzzlePlatformGameMode.h"
#include "MP_PuzzlePlatformCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMP_PuzzlePlatformGameMode::AMP_PuzzlePlatformGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
