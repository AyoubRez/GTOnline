// Copyright Epic Games, Inc. All Rights Reserved.

#include "GTOnlineGameMode.h"
#include "GTOnlineCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGTOnlineGameMode::AGTOnlineGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/_Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
