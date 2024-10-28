// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BotsStatisticList.generated.h"

/**
 * 
 */
UCLASS()
class DOGPLAY_API UBotsStatisticList : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "ChildWidgets")
	TArray<class UBotStatistic*> BotsStatistics;


	UFUNCTION(BlueprintCallable, Category = "ChildWidgets")
	void SortChildWidgets(const bool bIsAscending);
	
};
