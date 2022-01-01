// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || DistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Condition Checked"));
	//If Conditions Met, Fire
	if (!PlayerPawn || !PlayerPawn->IsPlayerAlive())
	{
		return;
	}

	if (DistanceToPlayer() <= FireRange)
	{
		Fire();
	}
	//is player valid || dead
	//If player is in range
}


float APawnTurret::DistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());

}
