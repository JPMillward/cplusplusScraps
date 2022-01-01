// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/GameModeBase.h"
#include "KrazyKartsGameMode.generated.h"


UCLASS(minimalapi)
class AKrazyKartsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	

	bool IsRaceActive();

	bool IsInputLocked();

protected:

private:
	
	class AKartGameState* KartGameState;

	AKrazyKartsGameMode();

	void StartPlay() override;

	void NotifyRaceState();

	void PostLogin(APlayerController* NewPlayer) override;

	void BeginRace();

	void EndRace();
};



