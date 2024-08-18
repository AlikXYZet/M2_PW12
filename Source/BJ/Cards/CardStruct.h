﻿#pragma once

#include "CoreMinimal.h"
#include "CardStruct.generated.h"



// Номинал карты(достоинство)
UENUM(BlueprintType)
enum struct ERank : uint8
{
	NONE = 0,
	Ace = 1, // Туз
	N2,
	N3,
	N4,
	N5,
	N6,
	N7,
	N8,
	N9,
	N10,
	Jack = 10,  // Валет
	Queen = 10, // Дама
	King = 10,  // Король
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

	ERank Rank = ERank::NONE;
	ESuit Suit = ESuit::NONE;
};

