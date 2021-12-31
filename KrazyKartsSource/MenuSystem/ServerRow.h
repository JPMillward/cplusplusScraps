// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_MP_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

private:


protected:
//	bool Initialize() override;

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextServerOwner;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextPlayerInfo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextPing;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonSelectRow;

	UPROPERTY()
	class UMainMenu* ParentClass;

	uint32 ServerIndex;

	UPROPERTY(EditAnywhere, Category = "Header")
	bool IsHeader = false;

	UPROPERTY(BlueprintReadOnly)
	bool IsSelected;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor DefaultColor;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor HoverColor;

	UFUNCTION()
	void OnClicked();

	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnUnhovered();

	void SetupRow(class UMainMenu* Parent, uint32 Index);
};
