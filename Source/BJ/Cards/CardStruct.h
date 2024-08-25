#pragma once

// Base:
#include "CoreMinimal.h"

// Generated:
#include "CardStruct.generated.h"
//--------------------------------------------------------------------------------------



// Номинал карты (достоинство)
UENUM(BlueprintType)
enum struct ERank : uint8
{
	NONE = 0,
	Ace = 1, // Туз
	N2		UMETA(DisplayName = "2"),
	N3		UMETA(DisplayName = "3"),
	N4		UMETA(DisplayName = "4"),
	N5		UMETA(DisplayName = "5"),
	N6		UMETA(DisplayName = "6"),
	N7		UMETA(DisplayName = "7"),
	N8		UMETA(DisplayName = "8"),
	N9		UMETA(DisplayName = "9"),
	N10		UMETA(DisplayName = "10"),
	Jack,  // Валет
	Queen, // Дама
	King,  // Король
};

// Масть карты
UENUM(BlueprintType)
enum struct ESuit : uint8
{
	NONE = 0,
	Hearts,   // Черви
	Diamonds, // Бубны
	Clubs,    // Трефы
	Spades    // Пики
};



// Данные карты
USTRUCT(BlueprintType)
struct FCardData
{
	GENERATED_BODY()

	FCardData(ERank iRank = ERank::NONE, ESuit iSuit = ESuit::NONE)
		: Rank(iRank), Suit(iSuit) {};

	// Номинал карты (достоинство)
	ERank Rank = ERank::NONE;

	// Масть карты
	ESuit Suit = ESuit::NONE;
};

