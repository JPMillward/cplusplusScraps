// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/Widget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"
#include "GameFramework/PlayerController.h"
#include "Math/Color.h"
#include "Misc/Optional.h"
#include "ServerRow.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (ButtonToJoinMenu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ButtonToJoinMenu Bound"));
		ButtonToJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	}

	if (ButtonToHostMenu != nullptr)
	{

		UE_LOG(LogTemp, Warning, TEXT("ButtonToHostMenu Bound"));
		ButtonToHostMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);
	}

	if (ButtonToMainFromHost != nullptr)
	{

		UE_LOG(LogTemp, Warning, TEXT("ButtonToMainFromHost Bound"));
		ButtonToMainFromHost->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	}

	if (ButtonToMainFromJoin != nullptr)
	{

		UE_LOG(LogTemp, Warning, TEXT("ButtonToMainFromJoin Bound"));
		ButtonToMainFromJoin->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	}

	if (ButtonHostServer != nullptr)
	{
		ButtonHostServer->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	}

	if (ButtonJoinServer != nullptr)
	{
		ButtonJoinServer->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	}


	return true;

}

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBP(TEXT("/Game/MenuSystem/WBP_ServerRow_Base"));
	if (ServerRowBP.Class != nullptr)
	{
		ServerRowClass = ServerRowBP.Class;
		
	}

	return;
}

void UMainMenu::HostServer()
{

	if (MenuInterface != nullptr)
	{
		FString ServerName = InputServerName->Text.ToString();
		MenuInterface->Host(ServerName);
	}
	UE_LOG(LogTemp, Warning, TEXT("Hosting Lobby Named: %s"), *InputServerName->Text.ToString());
	return;
}

void UMainMenu::JoinServer()
{

	if (MenuInterface != nullptr && SelectedIndex.IsSet())
	{

		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No ServerList Widget Found"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Gonna join a server bud!"));
	return;
}

void UMainMenu::OpenHostMenu()
{
	if (HostMenu != nullptr)
	{

		UE_LOG(LogTemp, Warning, TEXT("HostMenu Called."));
		MenuSwitch->SetActiveWidget(HostMenu);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable To Call Function OpenHostMenu?"));
	}
	return;
}

void UMainMenu::OpenJoinMenu()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index Not Set"));
	}

	if (JoinMenu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenJoinMenu Called"));
		MenuSwitch->SetActiveWidget(JoinMenu);
	}

	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshResults();
	}

	return;
}

void UMainMenu::OpenMainMenu()
{
	if (MainMenu != nullptr)
	{
		MenuSwitch->SetActiveWidget(MainMenu);
	}

}


void UMainMenu::SetupMenu()
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

	return;
}


void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
	Super::TearDownMenu();

	return;
}

void UMainMenu::SetServerList(TArray<FServerData> ServerData)
{
	UWorld* World = this->GetWorld();

	if (World == nullptr) return;

	PanelServerList->ClearChildren();

	uint32 ServerIndex = 0;
	for (const FServerData& ServerInfo : ServerData)
	{
		
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);

		if (PanelServerList != nullptr)
		{

			ServerRow->TextServerName->SetText(FText::FromString(ServerInfo.ServerName));
			ServerRow->TextServerOwner->SetText(FText::FromString(ServerInfo.ServerOwner));
			ServerRow->TextPlayerInfo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), ServerInfo.CurrentPlayers, ServerInfo.MaxPlayers)));
			ServerRow->TextPing->SetText(FText::AsNumber(ServerInfo.Ping));
			ServerRow->SetupRow(this, ServerIndex);



			++ServerIndex;
			PanelServerList->AddChild(ServerRow);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Server Widget Found"));
		}
	} 

}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateWidgetSelect();
}

void UMainMenu::UpdateWidgetSelect()
{
	for (int32 Child = 0; Child < PanelServerList->GetChildrenCount(); Child++)
	{
		UServerRow* Row = Cast<UServerRow>(PanelServerList->GetChildAt(Child));
		if (Row != nullptr)
		{
			Row->IsSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == Child);
			if (Row->IsSelected)
			{
				FLinearColor Selected = FLinearColor(1, 0, 1);
				Row->ButtonSelectRow->SetColorAndOpacity(Selected);
			}
			else
			{
				FLinearColor NotSelected = FLinearColor(1, 1, 1);
				Row->ButtonSelectRow->SetColorAndOpacity(NotSelected);
			}
		}
	}
}
