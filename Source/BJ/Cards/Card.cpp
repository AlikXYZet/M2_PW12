// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "Card.h"

// UE:
#include "Components/TextRenderComponent.h"
#include "Components/DecalComponent.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
ACard::ACard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // Предварительно



	/* ---   Visualization   --- */

	// Корневой компонент
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	CardMesh->SetupAttachment(RootComponent);
	CardMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.5f));
	CardMesh->SetRelativeScale3D(FVector(1.26f, 0.88f, 0.01f));

	RankText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Rank"));
	RankText->SetupAttachment(RootComponent);
	RankText->SetRelativeLocation(FVector(-20.f, 0.f, 1.5f));
	RankText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	RankText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	RankText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	RankText->SetTextRenderColor(FColor::Red);
	RankText->SetText(TEXT("[ Rank ]"));

	SuitDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Suit Decal"));
	SuitDecal->SetupAttachment(RootComponent);
	SuitDecal->SetRelativeTransform(FTransform(
		FRotator(90.f, 270.f, 0.f), // Аналог (90.f, 90.f, 180.f)
		FVector(20.f, 0.f, 1.f),
		FVector(0.005f, 0.1f, 0.1f)));
	//-------------------------------------------
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

	// Контроль перемещения
	if (bIsMovingToNewLocation)
	{
		FVector lCurrentLocation = GetActorLocation();

		// Контроль близости к новой локации
		if ((lCurrentLocation - NewLocation).Size() < DeviationTolerance)
		{
			SetActorLocation(NewLocation);
			bIsMovingToNewLocation = false;
		}
		else
		{
			// Плавная интерполяция перемещения
			SetActorLocation(FMath::VInterpTo(lCurrentLocation, NewLocation, DeltaTime, MovementSpeed));
		}
	}
}
//--------------------------------------------------------------------------------------



/* ---   CardData   --- */

void ACard::SetCardData(const FCardData& iData)
{
	// Установить новое значение
	CardData = iData;

	// Установка цвета по масти
	if (CardData.Suit == ESuit::Clubs
		|| CardData.Suit == ESuit::Spades)
	{
		RankText->SetTextRenderColor(FColor::Black);
	}

	RankText->SetText(UEnum::GetDisplayValueAsText(CardData.Rank));

	// Установка Материала Декали, соответствующий масти
	switch (CardData.Suit)
	{
	case ESuit::Hearts:
		if (HeartsMaterial)
		{
			SuitDecal->SetDecalMaterial(HeartsMaterial);
		}
		break;

	case ESuit::Diamonds:
		if (HeartsMaterial)
		{
			SuitDecal->SetDecalMaterial(DiamondsMaterial);
		}
		break;

	case ESuit::Clubs:
		if (HeartsMaterial)
		{
			SuitDecal->SetDecalMaterial(ClubsMaterial);
		}
		break;

	case ESuit::Spades:
		if (HeartsMaterial)
		{
			SuitDecal->SetDecalMaterial(SpadesMaterial);
		}
		break;
	}
}

ERank ACard::GetCardRank() const
{
	return CardData.Rank;
}

void ACard::GoToLocation(const FVector& iToLocation)
{
	bIsMovingToNewLocation = true;

	NewLocation = iToLocation;
}
//--------------------------------------------------------------------------------------
