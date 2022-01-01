// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "KrazyKartsPlayerState.generated.h"


/**
 * 
 */
UCLASS()
class KRAZYKARTS_API AKrazyKartsPlayerState : public APlayerState
{
	GENERATED_BODY()

private:

	AKrazyKartsPlayerState();
	
	void IncrementCheckPointCount();

	void ClearCheckPointCount();

	void IncrementLapCount();

	void SetPlayerPosition(uint32 NewPosition);

	void HandleLapTiming();

protected:
	UPROPERTY(BlueprintReadOnly,  Category = "PlayerData")
	int32 CheckPointCount;

	UPROPERTY(BlueprintReadOnly,  Category = "PlayerData")
	int32 LapCount;

	UPROPERTY(BlueprintReadOnly,  Category = "PlayerData")
	int32 PlayerPosition;

	UPROPERTY(BlueprintReadOnly,  Category = "PlayerData")
	float LapTimer;
	
	UPROPERTY(BlueprintReadOnly, Category = "PlayerData")
	TArray<float> LapTimes;
	
};
