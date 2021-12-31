// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBase.h"
#include "Components/Widget.h"


bool UMenuBase::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}
	
	return true;
}


void UMenuBase::SetupMenu()
{
	if (this == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("Uhhhh?"));
		return;
	}
	this->AddToViewport();
	return;
}

void UMenuBase::TearDownMenu()
{
	this->RemoveFromViewport();


	FInputModeGameOnly InputModeData;

	UWorld* World = GetWorld();
	if (World == nullptr) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetInputMode(InputModeData);
		PlayerController->SetShowMouseCursor(false);
	}

	return;
}

void UMenuBase::SetMenuInterface(IMenuInterface* SomeMenuInterface)
{
	if (SomeMenuInterface != nullptr)
	{
		this->MenuInterface = SomeMenuInterface;
	}
	return;
}
