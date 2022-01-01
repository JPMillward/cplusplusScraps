// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KartGameState.generated.h"

/**
 * 
 */
UCLASS()
class KRAZYKARTS_API AKartGameState : public AGameStateBase
{
	GENERATED_BODY()

	AKartGameState(const FObjectInitializer& ObjectInitializer);

public:

	UFUNCTION(BlueprintCallable, Category = Game)
	float GetTotalTime();

	UFUNCTION(BlueprintCallable, Category = Game)
	bool IsRaceActive() const;

	UFUNCTION(BlueprintCallable, Category = Game)
	void SetRaceActive(bool bIsActive);


protected:


private:
	/** number of teams in current game */
	UPROPERTY(Transient, Replicated)
	uint32 PlayerCount;

	/** total race time */
	UPROPERTY(Transient, Replicated)
	float TotalTime;

	/** is timer paused? */
	UPROPERTY(Transient, Replicated)
	bool bTimerPaused;

	/** is timer paused? */
	UPROPERTY(Transient, Replicated)
	bool bIsRaceActive;

};
