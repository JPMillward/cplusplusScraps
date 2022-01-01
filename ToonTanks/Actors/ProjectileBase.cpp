// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	ProjectileTrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ProjectileTrailParticle->SetupAttachment(RootComponent);

}


void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSFX, GetActorLocation());

}


void AProjectileBase::Tick(float DeltaTime)
{
}


void AProjectileBase::PostActorCreated()
{

	Super::PostActorCreated();

	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	InitialLifeSpan = 3.0f;
}


void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GetOwner())
	{
		AActor* MyOwner = GetOwner();
		if (!MyOwner)
		{
			return;
		}

		if (OtherActor && OtherActor != this && OtherActor != MyOwner)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSFX, GetActorLocation());
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitShake);
			Destroy();
		}
	}
}
