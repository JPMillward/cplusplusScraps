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
	
	void IncrementCheckPointCount();

	void ClearCheckPointCount();

	void IncrementLapCount();

	void SetPlayerPosition(uint32 NewPosition);

	void HandleLapTiming();

protected:
	UPROPERTY(BlueprintReadOnly,  Category = "PlayerData")
	int32 CheckPointCount = 0;

	UPROPERTY(BlueprintReadOnly,  Category = "PlayerData")
	int32 LapCount = 0;

	UPROPERTY(BlueprintReadOnly,  Category = "PlayerData")
	int32 PlayerPosition = 0;

	UPROPERTY(BlueprintReadOnly,  Category = "PlayerData")
	float LapTimer = 0.f;
	
	UPROPERTY(BlueprintReadOnly, Category = "PlayerData")
	TArray<float> LapTimes;
	
};
