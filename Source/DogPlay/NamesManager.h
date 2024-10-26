// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "NamesManager.generated.h"

/**
 * 
 */
UCLASS()
class DOGPLAY_API ANamesManager : public AInfo
{
	GENERATED_BODY()

public:
	FText GetRandomUniqName();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Names")
	FText DefaultName = FText::FromString("Cabaka"); 
	
	UPROPERTY(EditDefaultsOnly, Category = "Names")
	TArray<FText> Names;
	
	TArray<FText> RemainingNames;
	
};
