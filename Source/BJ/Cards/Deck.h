﻿#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// UE:
#include "Components/TextRenderComponent.h"

// Interaction:
#include "BJ/Cards/CardStruct.h"

// Generated:
#include "Deck.generated.h"
//--------------------------------------------------------------------------------------



UCLASS()
class BJ_API ADeck : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	ADeck();
	//-------------------------------------------


	/* ---   Base   --- */

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//-------------------------------------------



	/* ---   Visualization   --- */

	// Меш визуализации колоды
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* DeckMesh = nullptr;
	// Текст количества карт
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* CardsNumberText = nullptr;
	//-------------------------------------------



	/* ---   CardData   --- */

	// Сбросить колоду с перетасовкой
	void Reset();
	// Обновить данные о текущем количесте карт
	void UpdateData();
	// Перетасовать колоду
	void Shuffle();

	/** 
	* Получить верхнюю карту
	* @return	Данные новой карты
	*/
	FCardData TakeUpperCard();

	// Получить текущее количество карт
	int32 GetNumOfCards() const;
	//-------------------------------------------



private:

	/* ---   CardData   --- */

	// Все типы карт
	TArray<FCardData> AllCardsType;
	//-------------------------------------------
};
