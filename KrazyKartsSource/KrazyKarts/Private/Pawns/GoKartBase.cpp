// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/GoKartBase.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Math/TransformNonVectorized.h"
#include "Math/Quat.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "Components/InputComponent.h"


// Sets default values
AGoKartBase::AGoKartBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;


	MovementComponent = CreateDefaultSubobject<UGoKartMovementComponent>(TEXT("MovementComponent"));
	MovementReplicator = CreateDefaultSubobject<UGoKartMovementReplicator>(TEXT("MovementReplicator"));

	return;
}

FString GetEnumText(ENetRole Role)
{
	switch (Role)
	{
	case ROLE_None:
		return "None";
	case ROLE_SimulatedProxy:
		return "SimulatedProxy";
	case ROLE_AutonomousProxy:
		return "AutonomousProxy";
	case ROLE_Authority:
		return "Authority";
	default:
		return "ERROR";
	}
}

// Called to bind functionality to input
void AGoKartBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKartBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKartBase::MoveRight);

}

// Called when the game starts or when spawned
void AGoKartBase::BeginPlay()
{
	Super::BeginPlay();


	if (HasAuthority())
	{
		NetUpdateFrequency = 1;
	}
	SetReplicateMovement(false);
	return;
}


// Called every frame
void AGoKartBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugString(GetWorld(), FVector(0, 0, 100), GetEnumText(GetLocalRole()), this, FColor::Green, DeltaTime);

}




void AGoKartBase::MoveForward(float Value)
{
	if (MovementComponent == nullptr) return;
	MovementComponent->SetThrottle(Value);
}

void AGoKartBase::MoveRight(float Value)
{
	if (MovementComponent == nullptr) return;
	MovementComponent->SetSteeringThrow(Value);
}

void AGoKartBase::UpdatePlayerPosition()
{
	if (GetController() != nullptr)
	{
		return;
	}

}
