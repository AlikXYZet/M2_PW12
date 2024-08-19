﻿// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Card.h"



/* ---   Constructors   --- */

// Sets default values
ACard::ACard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно



	/* ---   Visualization   --- */

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = SceneComponent;

	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	CardMesh->SetupAttachment(RootComponent);
	CardMesh->SetRelativeScale3D(FVector(1.26f, 0.88f, 0.01f));

	RankText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Rank"));
	RankText->SetupAttachment(RootComponent);
	RankText->SetRelativeLocation(FVector(-20.f, 0.f, 1.f));
	RankText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	RankText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	RankText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	RankText->SetTextRenderColor(FColor::Red);

	SuitText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Suit"));
	SuitText->SetupAttachment(RootComponent);
	SuitText->SetRelativeLocation(FVector(20.f, 0.f, 1.f));
	SuitText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	SuitText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	SuitText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	SuitText->SetTextRenderColor(FColor::Red);
	//-------------------------------------------
}

ACard::ACard(const FCardData& iCardData)
	: ACard()
{
	CardData = iCardData;
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

void ACard::BeginPlay()
{
	Super::BeginPlay();

	// Установка цвета по масти
	if (CardData.Suit == ESuit::Clubs
		|| CardData.Suit == ESuit::Spades)
	{
		RankText->SetTextRenderColor(FColor::Black);
		SuitText->SetTextRenderColor(FColor::Black);
	}
}

void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//--------------------------------------------------------------------------------------
