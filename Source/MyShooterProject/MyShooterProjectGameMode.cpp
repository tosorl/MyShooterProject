// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyShooterProjectGameMode.h"
#include "MyShooterProjectPawn.h"

AMyShooterProjectGameMode::AMyShooterProjectGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AMyShooterProjectPawn::StaticClass();
}

