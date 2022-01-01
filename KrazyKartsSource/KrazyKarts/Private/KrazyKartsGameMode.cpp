// Copyright Epic Games, Inc. All Rights Reserved.

#include "KrazyKartsGameMode.h"
#include "KrazyKarts.h"
#include "KrazyKartsPlayerState.h"
#include "Pawns/GoKartBase.h"

AKrazyKartsGameMode::AKrazyKartsGameMode()
{
	DefaultPawnClass = AGoKartBase::StaticClass();
	PlayerStateClass = AKrazyKartsPlayerState::StaticClass();

}

void AKrazyKartsGameMode::StartPlay()
{
	Super::StartPlay();

}

void AKrazyKartsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
