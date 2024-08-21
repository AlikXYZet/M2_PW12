// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "BJ_UserWidget.h"



/* ---   Interaction with Table   --- */

void UBJ_UserWidget::CommandToHit()
{
	CurrentTable->CommandToHit();
}

void UBJ_UserWidget::CommandToStand()
{
	CurrentTable->CommandToStand();
}

void UBJ_UserWidget::CommandToSurrender()
{
	CurrentTable->CommandToSurrender();
}
//--------------------------------------------------------------------------------------
