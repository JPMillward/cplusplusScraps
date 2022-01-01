// Copyright Epic Games, Inc. All Rights Reserved.

#include "KrazyKartsGameMode.h"
#include "KartGameState.h"
#include "Player/KrazyKartsPlayerController.h"
#include "KrazyKarts.h"
#include "KrazyKartsPlayerState.h"
#include "Pawns/GoKartBase.h"

AKrazyKartsGameMode::AKrazyKartsGameMode()
{
	DefaultPawnClass = AGoKartBase::StaticClass();
	PlayerStateClass = AKrazyKartsPlayerState::StaticClass();
	GameStateClass = AKartGameState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;

}

void AKrazyKartsGameMode::StartPlay()
{
	Super::StartPlay();
	KartGameState = GetGameState<AKartGameState>();
}

void AKrazyKartsGameMode::NotifyRaceState()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		
		AKrazyKartsPlayerController* VehicleController = Cast<AKrazyKartsPlayerController>(*It);
		if (KartGameState != nullptr && VehicleController)
		{
			VehicleController->UpdatePlayerState(KartGameState->IsRaceActive());
		}
	}
}

void AKrazyKartsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AKrazyKartsGameMode::BeginRace()
{
	if (KartGameState)
	{
		KartGameState->SetRaceActive(true);
	}
}
