// Copyright Epic Games, Inc. All Rights Reserved.

#include "DogPlayGameMode.h"

#include "DogGameGameState.h"
#include "DogPlayCharacter.h"
#include "DogPlayPlayerController.h"
#include "NamesManager.h"
#include "GameFramework/PlayerState.h"
#include "UObject/ConstructorHelpers.h"

FText ADogPlayGameMode::GetRandomUniqName() const
{
	if(IsValid(NamesManager))
	{
		return NamesManager->GetRandomUniqName();
	}
	return FText::FromString("");
}

void ADogPlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(NamesManagerClass))
	{
		NamesManager = GetWorld()->SpawnActor<ANamesManager>(NamesManagerClass, FActorSpawnParameters{});
	}

	ADogGameGameState* LocalGameState = GetGameState<ADogGameGameState>();
	if(LocalGameState )
	{
		LocalGameState->SetMaxGameSessionTime(MaxGameSessionTime);
		LocalGameState->OnGameTimeIsOverDelegate.BindUObject(this, &ADogPlayGameMode::EndMatch);
	}
	FTimerHandle LocalTimerHandle;
	GetWorldTimerManager().SetTimer(LocalTimerHandle, this, &ADogPlayGameMode::StartMatch, 1.0f, false);
}

void ADogPlayGameMode::EndMatch()
{
	if (!IsMatchInProgress())
	{
		return;
	}


	for (const APlayerState* PlayerState : GameState->PlayerArray)
	{
		if (APlayerController* PC = PlayerState->GetPlayerController())
		{
			// Inform the players about the end of the match
			ADogPlayPlayerController* GameplayEPlayerController = Cast<ADogPlayPlayerController>(PC);
			if (IsValid(GameplayEPlayerController))
			{
				GameplayEPlayerController->Client_OnMatchIsOver();
			}
		}
	}
	
	Super::EndMatch();
}
