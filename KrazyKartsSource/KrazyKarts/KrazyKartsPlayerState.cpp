// Fill out your copyright notice in the Description page of Project Settings.


#include "KrazyKartsPlayerState.h"


void AKrazyKartsPlayerState::IncrementCheckPointCount()
{
	++CheckPointCount;
}

void AKrazyKartsPlayerState::ClearCheckPointCount()
{
	CheckPointCount = 0;
}

void AKrazyKartsPlayerState::IncrementLapCount()
{
	++LapCount;
}

void AKrazyKartsPlayerState::SetPlayerPosition(uint32 NewPosition)
{
	PlayerPosition = NewPosition;
}

void AKrazyKartsPlayerState::HandleLapTiming()
{	
	LapTimes.Add(LapTimer);
	LapTimer = 0;
}