// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KartGameState.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "KrazyKarts.h"


AKartGameState::AKartGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerCount = 0;
	TotalTime = 0;
	
	bTimerPaused = false;
	bIsRaceActive = false;

	// need to tick when paused to check king state.
	PrimaryActorTick.bCanEverTick = true;
	SetTickableWhenPaused(true);
  

}

float AKartGameState::GetTotalTime()
{
	return TotalTime;
}

bool AKartGameState::IsRaceActive() const
{
	return bIsRaceActive;
}

void AKartGameState::SetRaceActive(bool bIsActive)
{
	bIsRaceActive = bIsActive;
}

void AKartGameState::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( AKartGameState, PlayerCount );
	DOREPLIFETIME( AKartGameState, TotalTime );
	DOREPLIFETIME( AKartGameState, bTimerPaused );
	DOREPLIFETIME( AKartGameState, bIsRaceActive );
	
}