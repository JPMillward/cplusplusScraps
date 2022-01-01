// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"


class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

	APawnTank* PlayerTank;
	APlayerControllerBase* PlayerController;


	int32 TurretTargets = 0;

	
	void HandleGameStart();
	
	void HandleGameOver(bool PlayerWon);

	int32 GetTurretTargetCount();
public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

};
