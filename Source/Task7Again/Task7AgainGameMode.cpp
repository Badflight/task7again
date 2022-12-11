// Copyright Epic Games, Inc. All Rights Reserved.

#include "Task7AgainGameMode.h"
#include "Task7AgainCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATask7AgainGameMode::ATask7AgainGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
