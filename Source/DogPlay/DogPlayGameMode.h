// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DogPlayGameMode.generated.h"

class ANamesManager;

UCLASS()
class DOGPLAY_API ADogPlayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FText GetRandomUniqName() const;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	ANamesManager* NamesManager;
	
	UPROPERTY(EditDefaultsOnly, Category = "Bots")
	TSubclassOf<ANamesManager> NamesManagerClass;
	
};
