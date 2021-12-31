// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "Components/Button.h"
#include "MainMenu.h"
//
//bool UServerRow::Initialize()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Initialized Server Row Widget"));
//	return true;
//}

void UServerRow::OnClicked()
{
	ParentClass->SelectIndex(ServerIndex);
}

void UServerRow::OnHovered()
{
	if (!IsSelected)
	{
		FLinearColor Hovered = FLinearColor(0.5, 0.5, 0.75);
		ButtonSelectRow->SetColorAndOpacity(Hovered);
	}
}

void UServerRow::OnUnhovered()
{
	if (!IsSelected)
	{
		DefaultColor = FLinearColor(1, 1, 1);
		ButtonSelectRow->SetColorAndOpacity(DefaultColor);
	}
}



void UServerRow::SetupRow(UMainMenu* Parent, uint32 Index)
{
	ParentClass = Parent;
	ServerIndex = Index;

	if (!IsHeader)
	{
		ButtonSelectRow->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
		ButtonSelectRow->OnHovered.AddDynamic(this, &UServerRow::OnHovered);
		ButtonSelectRow->OnUnhovered.AddDynamic(this, &UServerRow::OnUnhovered);
	}
	if (IsHeader)
	{
		this->bIsEnabled = false;
 	}

}
