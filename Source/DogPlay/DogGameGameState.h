// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DogGameGameState.generated.h"

DECLARE_DELEGATE(OnGameTimeIsOver)
/**
 * 
 */
UCLASS()
class DOGPLAY_API ADogGameGameState : public AGameState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Replicated)
	int32 MaxGameSessionTime = 0;
	
public:
	OnGameTimeIsOver OnGameTimeIsOverDelegate;
	
	virtual void DefaultTimer() override;

	void SetMaxGameSessionTime(int32 NewGameSessionTime);

	UFUNCTION(BlueprintPure)
	int32 GetMaxGameSessionTime() const{return MaxGameSessionTime;};

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
