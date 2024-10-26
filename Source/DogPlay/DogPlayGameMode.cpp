// Copyright Epic Games, Inc. All Rights Reserved.

#include "DogPlayGameMode.h"
#include "DogPlayCharacter.h"
#include "NamesManager.h"
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
}
