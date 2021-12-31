// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString ServerName;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	uint16 Ping;
	FString ServerOwner;
};
/**
 * 
 */
UCLASS()
class UNREAL_MP_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

protected:

	bool Initialize() override;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	

private:

	TSubclassOf<class UServerRow> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonHostServer;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonJoinServer;

	
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonToJoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonToHostMenu;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* PanelServerList;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonToMainFromJoin;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonToMainFromHost;
	
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* InputServerName;
	
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitch;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;
	
	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	TOptional<uint32> SelectedIndex;



	void UpdateWidgetSelect();

public:

	UMainMenu(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();


	void SetupMenu() override;

	virtual void OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld) override;

	void SetServerList(TArray<FServerData> ServerData);

	void SelectIndex(uint32 Index);
};
