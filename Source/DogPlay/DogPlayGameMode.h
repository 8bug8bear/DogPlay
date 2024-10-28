// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DogPlayGameMode.generated.h"

class ANamesManager;

UCLASS()
class DOGPLAY_API ADogPlayGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FText GetRandomUniqName() const;

protected:
	virtual void BeginPlay() override;

	virtual void EndMatch() override;

	
	UPROPERTY()
	ANamesManager* NamesManager;
	
	UPROPERTY(EditDefaultsOnly, Category = "Bots")
	TSubclassOf<ANamesManager> NamesManagerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Time)
	int32 MaxGameSessionTime = 30; // 5 minutes

	// Will players spawn in random spawn points after death, or selected in advance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Respawn)
	bool bIsStaticSpawnPoints = false;
	
};
