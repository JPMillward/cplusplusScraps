// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/GameModeBase.h"
#include "KrazyKartsGameMode.generated.h"

UCLASS(minimalapi)
class AKrazyKartsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AKrazyKartsGameMode();

	void StartPlay() override;

	void PostLogin(APlayerController* NewPlayer) override;

	void BeginRace();

	void EndRace();

	
};



