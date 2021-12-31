// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKartMovementComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGoKartMovementComponent::UGoKartMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGoKartMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetWorld() != nullptr)
	{
		GravityAcceleration = -GetWorld()->GetGravityZ() * .001;
	}
	
}


// Called every frame
void UGoKartMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwnerRole() == ROLE_AutonomousProxy || GetOwner()->GetRemoteRole() == ROLE_SimulatedProxy)
	{
		LastMove = CreateMove(DeltaTime);
		SimulateMove(LastMove);
	}
}


void UGoKartMovementComponent::SimulateMove(const FGoKartMove& Move)
{

	FVector Force = GetOwner()->GetActorForwardVector() * MaxDrivingForce * Move.Throttle;

	Force += GetAirResistance();
	Force += GetRollingResistance();

	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * Move.DeltaTime;

	ApplyRotation(Move.DeltaTime, Move.SteeringThrow);

	//100 for Meters to CentiMeters
	UpdateLocationFromVelocity(Move.DeltaTime);
	return;
}

void UGoKartMovementComponent::SetVelocity(FVector NewVelocity)
{
	Velocity = NewVelocity;
}

FVector UGoKartMovementComponent::GetVelocity()
{
	return Velocity;
}

void UGoKartMovementComponent::SetThrottle(float NewThrottle)
{
	Throttle = NewThrottle;
}

void UGoKartMovementComponent::SetSteeringThrow(float NewSteeringThrow)
{
	SteeringThrow = NewSteeringThrow;
}


FGoKartMove UGoKartMovementComponent::CreateMove(float DeltaTime)
{
	FGoKartMove Move;
	Move.SteeringThrow = SteeringThrow;
	Move.Throttle = Throttle;
	Move.DeltaTime = DeltaTime;
	Move.Time = GetWorld()->GetTimeSeconds();

	return Move;
}


void UGoKartMovementComponent::ApplyRotation(float DeltaTime, float MoveSteeringThrow)
{

	float DeltaLocation = FVector::DotProduct(GetOwner()->GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationValue = DeltaLocation / MinTurnRadius * MoveSteeringThrow;
	FQuat DeltaRotation(GetOwner()->GetActorUpVector(), RotationValue);

	Velocity = DeltaRotation.RotateVector(Velocity);
	GetOwner()->AddActorWorldRotation(DeltaRotation);

	return;
}


FVector UGoKartMovementComponent::GetAirResistance()
{
	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}


FVector UGoKartMovementComponent::GetRollingResistance()
{
	float NormalForce = GravityAcceleration * Mass;
	return -Velocity.GetSafeNormal() * NormalForce * RollingResistanceCoefficient;
}


void UGoKartMovementComponent::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * DeltaTime * 100;

	FHitResult Collision;
	GetOwner()->AddActorWorldOffset(Translation, true, &Collision);

	if (Collision.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}
