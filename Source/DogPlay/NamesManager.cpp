// Fill out your copyright notice in the Description page of Project Settings.


#include "NamesManager.h"

FText ANamesManager::GetRandomUniqName()
{
	if(Names.Num() == 0)
	{
		return DefaultName;
	}
	
	if(RemainingNames.Num() == 0)
	{
		RemainingNames = Names;
	}

	const int32 Index = FMath::RandRange(0, RemainingNames.Num() - 1);
	FText Name = RemainingNames[Index];
	RemainingNames.RemoveAt(Index);
	return Name;
}
