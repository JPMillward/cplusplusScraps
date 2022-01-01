// Fill out your copyright notice in the Description page of Project Settings.



#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(SpringArm);


}
// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	ThePlayer = Cast<APlayerController>(GetController());

}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();;
	//Hide, not Destroy for ease.

	bIsPlayerAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	UE_LOG(LogTemp, Warning, TEXT("APawnTank HandleDestruction Called."));

}

bool APawnTank::IsPlayerAlive()
{
	return bIsPlayerAlive;
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	if (ThePlayer)
	{
		FHitResult PlayerCursorTrace;
		ThePlayer->GetHitResultUnderCursor(ECC_Visibility, false, PlayerCursorTrace);
		FVector HitLocation = PlayerCursorTrace.ImpactPoint;
		
		RotateTurret(HitLocation);
	}

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotationInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
	
}

void APawnTank::CalculateRotationInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);

}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}