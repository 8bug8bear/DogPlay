// Copyright Epic Games, Inc. All Rights Reserved.


#include "DogPlayPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"


void ADogPlayPlayerController::Client_OnMatchIsOver_Implementation()
{
	FText WinnerName;
	int32 WinnerPoints;
	DetermineWinningBot(WinnerName, WinnerPoints);

	BPI_OnMatchIsOver(WinnerName, WinnerPoints);
}

void ADogPlayPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
