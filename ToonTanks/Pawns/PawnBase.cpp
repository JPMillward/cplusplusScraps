// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	CapsuleComponent->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnSpot = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnSpot->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{

	FVector CleanTarget = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = FVector(CleanTarget - StartLocation).Rotation();
	
	//Rotate Turret Mesh to face LookAtTarget passed
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	if (ProjectileClass)
	{	
		if (ProjectileSpawnSpot)
		{
			UE_LOG(LogTemp, Error, TEXT("SpawnPointFound"));
			FVector SpawnLocation = ProjectileSpawnSpot->GetComponentLocation();
			FRotator SpawnRotation = ProjectileSpawnSpot->GetComponentRotation();
			AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
			TempProjectile->SetOwner(this);
		}
		
	}
	//Get projectile spawn point
	//Location && rotation => Spawn Projectile firing from that
	
}

void APawnBase::HandleDestruction()
{

	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DestructionSFX, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathShake);
	
	//Death Effects
	//Camera Shake
	//Child Overrides

}