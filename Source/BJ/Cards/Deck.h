#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CardStruct.h"

#include "Deck.generated.h"

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

	// Корневой компонент
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent = nullptr;
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
	bool Shuffle();
	// Получить верхнюю карту
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
