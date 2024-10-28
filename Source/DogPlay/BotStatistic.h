// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BotStatistic.generated.h"

/**
 * 
 */
UCLASS()
class DOGPLAY_API UBotStatistic : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, Category = "Geters")
	int32 GetBotPoints() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Seters")
	void SetIsFirstStatistic(const bool bIsFirst) const;
	
};
