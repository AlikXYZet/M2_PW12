// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Card.h"



/* ---   Constructors   --- */

// Sets default values
ACard::ACard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно



	/* ---   Visualization   --- */

	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card"));
	RootComponent = CardMesh;
	CardMesh->SetRelativeScale3D(FVector(0.01f, 0.88f, 1.26f));

	RankText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Rank"));
	RankText->SetupAttachment(RootComponent);
	RankText->SetRelativeLocation(FVector(100.f, 0.f, 20.f));

	SuitText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Suit"));
	SuitText->SetupAttachment(RootComponent);
	SuitText->SetRelativeLocation(FVector(100.f, 0.f, -20.f));

	// Локальная меременная установки цвета
	FColor lNewColor = FColor::Red;

	// Установка цвета по масти
	if (CardData.Suit == ESuit::Clubs
		|| CardData.Suit == ESuit::Spades)
	{
		lNewColor = FColor::Black;
	}

	RankText->SetTextRenderColor(lNewColor);
	SuitText->SetTextRenderColor(lNewColor);
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

}

void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//--------------------------------------------------------------------------------------
