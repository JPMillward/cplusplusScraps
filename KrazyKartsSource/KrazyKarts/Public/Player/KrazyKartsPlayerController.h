// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KrazyKartsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KRAZYKARTS_API AKrazyKartsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void UpdatePlayerState(bool bIsEnabled);

private:
};
