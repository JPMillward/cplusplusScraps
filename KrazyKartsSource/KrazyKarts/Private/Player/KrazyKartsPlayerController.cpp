// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KrazyKartsPlayerController.h"

void AKrazyKartsPlayerController::UpdatePlayerState(bool bIsEnabled)
{
	if (bIsEnabled)
	{
		GetPawn()->EnableInput(this);
	}

	if (!bIsEnabled)
	{
		GetPawn()->DisableInput(this);
	}
}