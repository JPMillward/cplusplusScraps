// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"


USTRUCT()
struct FGoKartMove
{
	GENERATED_BODY()

	UPROPERTY()
	float Throttle;

	UPROPERTY()
	float SteeringThrow;

	UPROPERTY()
	float DeltaTime;

	UPROPERTY()
	float Time;

	bool IsValid() const
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	}
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Variable Access Methods
	void SetVelocity(FVector NewVelocity);
	FVector GetVelocity();

	void SetThrottle(float NewValue);

	void SetSteeringThrow(float NewValue);

	//Movement Simulation Functions
	void SimulateMove(const FGoKartMove& Move);

	FGoKartMove GetLastMove() {	return LastMove; };

	void SetBrakeLock();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	FGoKartMove LastMove;

	FVector GetRollingResistance();

	FVector GetAirResistance();

	FGoKartMove CreateMove(float DeltaTime);

	void UpdateLocationFromVelocity(float DeltaTime);

	void ApplyRotation(float DeltaTime, float SteeringThrow);

	float Throttle;
	float SteeringThrow;

	FVector Velocity;

	bool bBrakeLocked;

	//Mass of Kart in kilograms
	UPROPERTY(EditAnywhere)
	float Mass = 1000.f;

	//Force Applied to Car at full throttle. (N) Newtons
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	//In M
	UPROPERTY(EditAnywhere)
	float MinTurnRadius = 10;

	//0.3f - Tanks, 0.5f - Automobiles
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16.f;

	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = .1;

	//Newton would be proud. Calculated on BeginPlay based on World Settings.
	float GravityAcceleration;
		
};
