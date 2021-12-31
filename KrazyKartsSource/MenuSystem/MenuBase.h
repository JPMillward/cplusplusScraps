// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_MP_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
private:

protected:

	IMenuInterface* MenuInterface;

public:

	virtual bool Initialize();
	
	virtual void SetupMenu();

	virtual void TearDownMenu();

	
	void SetMenuInterface(IMenuInterface* SomeMenuInterface);
};
