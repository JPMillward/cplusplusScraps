// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TankGameMode = Cast<ATankGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	Health = DefaultHealth;
	UE_LOG(LogTemp, Error, TEXT("Health: %f"), Health);

}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Error, TEXT("Take Damage Called"));

	if ( Damage == 0 || Health == 0)
	{
		return;
	}
	
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	UE_LOG(LogTemp, Error, TEXT("Health: %f"), Health);


	if (Health <= 0)
	{
		if (TankGameMode)
		{
			TankGameMode->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ERROR: NO GAME MODE FOUND!"));
		}
	}
	
}
