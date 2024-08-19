// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Deck.h"

// Interaction:
#include "Card.h"
#include "BJ/Tools/MyRandom.h"


/* ---   Constructors   --- */

// Sets default values
ADeck::ADeck()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно


	/* ---   Visualization   --- */

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = SceneComponent;

	DeckMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Deck Mesh"));
	DeckMesh->SetupAttachment(RootComponent);
	DeckMesh->SetRelativeScale3D(FVector(1.26f, 0.88f, 0.52f));

	CardsNumberText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Cards Number"));
	CardsNumberText->SetupAttachment(RootComponent);
	CardsNumberText->SetRelativeLocation(FVector(0.f, 0.f, 27.f));
	CardsNumberText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	CardsNumberText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	CardsNumberText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	CardsNumberText->SetTextRenderColor(FColor::Red);
	//-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

// Called when the game starts or when spawned
void ADeck::BeginPlay()
{
	Super::BeginPlay();

	/* ---   CardData   --- */
	Reset();
	//-------------------------------------------
}

// Called every frame
void ADeck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//--------------------------------------------------------------------------------------



/* ---   CardData   --- */

void ADeck::Reset()
{
	// Предварительная подготовка массива
	AllCardsType.Reset(52);

	// Уменьшающийся цикл по мастям (кроме NONE)
	for (ESuit i = ESuit::Spades; i > ESuit::NONE; i = ESuit(uint8(i) - 1))
	{
		// Уменьшающийся цикл по номиналу (кроме NONE)
		for (ERank j = ERank::King; j > ERank::NONE; j = ERank(uint8(j) - 1))
		{
			// Сохранение всех возможных вариантов карт (одна колода из 52 карт)
			AllCardsType.Add(FCardData(j, i));
		}
	}

	UpdateData();
	Shuffle();
}

void ADeck::UpdateData()
{
	CardsNumberText->SetText(FString::Printf(TEXT("%d"), GetNumOfCards()));
}

bool ADeck::Shuffle()
{
	for (int i = AllCardsType.Num() - 1; i > 0; --i)
	{
		// Поменять местами i и random [0, i-1]
		AllCardsType.Swap(i, GetRandom(0, i - 1));
	}

	return true;
}

FCardData ADeck::TakeUpperCard()
{
	FCardData lResult = AllCardsType.Pop(false);

	UpdateData();

	return lResult;
}

int32 ADeck::GetNumOfCards() const
{
	return AllCardsType.Num();
}
//--------------------------------------------------------------------------------------
