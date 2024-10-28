// Fill out your copyright notice in the Description page of Project Settings.


#include "DogGameGameState.h"

#include "Net/UnrealNetwork.h"

void ADogGameGameState::DefaultTimer()
{
	Super::DefaultTimer();

	if(!IsNetMode(NM_DedicatedServer))
	{
		return;
	}
	
	if(ElapsedTime >= MaxGameSessionTime && IsMatchInProgress() && MaxGameSessionTime != 0) // In case the maximum time is not initialized
	{
		OnGameTimeIsOverDelegate.ExecuteIfBound();
	}
}

void ADogGameGameState::SetMaxGameSessionTime(int32 NewGameSessionTime)
{
	if(!IsNetMode(NM_DedicatedServer))
	{
		return;
	}
	if(NewGameSessionTime > 0)
	{
		MaxGameSessionTime = NewGameSessionTime;
	}
}

void ADogGameGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADogGameGameState, MaxGameSessionTime);
}
