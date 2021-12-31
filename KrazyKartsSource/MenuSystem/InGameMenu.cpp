// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Widget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
	bool Initialized = Super::Initialize();
	if (!Initialized) return false;

	if (ButtonCancel != nullptr)
	{
		ButtonCancel->OnClicked.AddDynamic(this, &UInGameMenu::CloseInGameMenu);
	}

	if (ButtonLeaveGame != nullptr)
	{
		ButtonLeaveGame->OnClicked.AddDynamic(this, &UInGameMenu::ExitGame);
	}

	return true;
}

void UInGameMenu::ExitGame()
{
	GetWorld()->GetFirstLocalPlayerFromController()->ConsoleCommand("quit");
	return;
}

void UInGameMenu::ExitToMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("ExitToMainMenu() Not Implemented!"));
	return;
}


void UInGameMenu::CloseInGameMenu()
{
	TearDownMenu();
	return;
}


void UInGameMenu::TearDownMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("TearDownMenu Called from InGameMenu"));
	Super::TearDownMenu();
	return;
}


void UInGameMenu::SetupMenu()
{
	Super::SetupMenu();

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	UWorld* World = GetWorld();
	if (World == nullptr) return;


	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetInputMode(InputModeData);
		PlayerController->SetShowMouseCursor(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("SetupMenu Called from InGameMenu"));

	return;
}
