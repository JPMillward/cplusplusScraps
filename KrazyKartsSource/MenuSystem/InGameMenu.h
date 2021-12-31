// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_MP_API UInGameMenu : public UMenuBase
{
	GENERATED_BODY()

protected:
	bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UWidget* OverlayMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonLeaveGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonCancel;

public:

	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void ExitToMainMenu();

	UFUNCTION()
	void CloseInGameMenu();
	
	void TearDownMenu() override;

	void SetupMenu() override;

};
