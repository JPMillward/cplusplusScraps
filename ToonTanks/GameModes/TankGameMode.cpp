// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"


void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();

	TurretTargets = GetTurretTargetCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();

	UE_LOG(LogTemp, Error, TEXT("Begin Play Called"));
}

void ATankGameMode::HandleGameStart()
{
	GameStart();

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController Not Found"));
	}
	if (PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay +  1, false);
	}
}

void ATankGameMode::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);

}

int32 ATankGameMode::GetTurretTargetCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	
	UE_LOG(LogTemp, Warning, TEXT("Number of Turrets: %i"), TurretActors.Num());
	return TurretActors.Num();
}

void ATankGameMode::ActorDied(AActor* DeadActor)
{

	UE_LOG(LogTemp, Error, TEXT("An Actor has Died."));
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerController)
		{
			PlayerController->SetPlayerEnabledState(false);
		}

	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TurretTargets == 0)
		{
			HandleGameOver(true);
		}

	}
	

}
