// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "BJ_PlayerController.h"

// Interaction:
#include "BJ_Pawn.h"
//--------------------------------------------------------------------------------------



/* ---   Base   --- */
void ABJ_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
}
//--------------------------------------------------------------------------------------