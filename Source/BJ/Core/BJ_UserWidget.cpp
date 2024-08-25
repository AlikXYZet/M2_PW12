// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "BJ_UserWidget.h"

// Interaction:
#include "BJ_Pawn.h"
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

void UBJ_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CurrentTable)
	{
		CurrentTable->InitTableForWidget(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UBJ_UserWidget::NativeConstruct : CurrentTable is NULLPTR"));
	}
}
//--------------------------------------------------------------------------------------



/* ---   Interaction with Table   --- */
void UBJ_UserWidget::CommandToHit()
{
	CurrentTable->WidgetCommandToHit();
}

void UBJ_UserWidget::CommandToStand()
{
	CurrentTable->WidgetCommandToStand();
}

void UBJ_UserWidget::CommandToSurrender()
{
	CurrentTable->WidgetCommandToSurrender();
}

void UBJ_UserWidget::CommandToNextRound()
{
	CurrentTable->StartRound();
}
//--------------------------------------------------------------------------------------
