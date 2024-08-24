#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// UE:
#include "Camera/CameraComponent.h"

// Interaction:
#include "BJ/Cards/CardStruct.h"

// Generated:
#include "BJ_Pawn.generated.h"



/* ---   Pre-declaration of classes   --- */
class ACard;
class ADeck;
//--------------------------------------------------------------------------------------



UCLASS()
class BJ_API ABJ_Pawn : public APawn
{
	GENERATED_BODY()

public:
	/* ---   Constructors   --- */

	// Sets default values for this pawn's properties
	ABJ_Pawn();
	//-------------------------------------------



	/* ---   Base   --- */

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Вызывается для привязки функциональности к входным данным
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	* Вызывается, когда эта пешка захвачена. Вызывается только на сервере (или в автономном режиме)
	* @param NewController - Контроллер, владеющий этой пешкой
	*/
	virtual void PossessedBy(AController* NewController) override;

	/** Вызывается, когда Контроллер больше не владеет данной Пешкой. */
	virtual void UnPossessed() override;
	//-------------------------------------------



	/* ---   Visualization   --- */

	/** Меш визуализации стола */
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TableMesh = nullptr;

	/** Точка местоположения Колоды */
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DeckLocationPoint = nullptr;

	/** Точка местоположения карт Крупье */
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CroupierCardsLocationPoint = nullptr;

	/** Точка местоположения карт Игрока */
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* PlayerCardsLocationPoint = nullptr;
	//-------------------------------------------



	/* ---   Camera   --- */

	/** Камера Игрока */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;
	//-------------------------------------------



	/* ---   Cards and Deck   --- */

	// Экземпляр карты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = "Deck of Cards")
	TSubclassOf<ACard> CardsType = nullptr;

	// Трансформ карт
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck of Cards")
	FTransform CardsTransform;

	// Экземпляр колоды
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = "Deck of Cards")
	TSubclassOf<ADeck> DeckType = nullptr;

	// Трансформ карт
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck of Cards")
	FTransform DeckTransform;
	//-------------------------------------------



	/* ---   Interaction from Widget   --- */

	/** Взять карту */
	void CommandToHit();

	/** Не брать карту */
	void CommandToStand();

	/** Разбить руку на две (только если есть две карты и они совпали по номиналу) */
	//void CommandToSplit();

	/** Удвоить ставку (после этого можно получить только одну карту) */
	//void CommandToDouble();

	/** Сдаться (завершает раунд с проигрышем) */
	void CommandToSurrender();

	/**
	* Функция сохранения указателя на Widget стола
	* (необходим для прямой передачи данных от Стола к Виджету)
	* @param iCurrentUserWidget - Указатель на текущий Widget стола
	*/
	void InitTableForWidget(class UBJ_UserWidget* iCurrentUserWidget);
	//-------------------------------------------



private:

	/* ---   Cards and Deck   --- */

	/** Указатель на колоду карт */
	ADeck* pDeck;

	/** Номиналы карт крупье */
	TArray<ERank> CroupierCardsData;
	/** Номиналы карт игрока */
	TArray<ERank> PlayerCardsData;

	// Разыгранные карты Крупье за текущий раунд
	TArray<ACard*> CroupierCards;

	// Разыгранные карты Игрока за текущий раунд
	TArray<ACard*> PlayerCards;

	// Ширина карты 
	float WidthOfCard;

	// Очистить стол от карт колоды
	void ClearOfCards();

	// Переместить все карты Руки для лучшего обзора
	void MoveAllCards(const USceneComponent* iPoint, TArray<ACard*>& iCards);

	// Пересчёт Трансформы (+Локациия, +Ротации и замена размера)
	FTransform ConversionTransform(const USceneComponent* iPoint, const FTransform& iSetTransform);

	// Создание и перемещение новой Карты
	ACard* CreateNewCard(TArray<ACard*>& iCards);
	//-------------------------------------------



	/* ---   Interaction from Widget   --- */

	/** Указатель на текущий виджет */
	class UBJ_UserWidget* pCurrentUserWidget = nullptr;
	//-------------------------------------------



	/* ---   Game Status   --- */

	/** Запуск хода Крупье */
	void CroupierTurn();

	/** Сценарий при раунде в ничью */
	void RoundIsDraw();

	/** Сценарий при победном раунде */
	void RoundIsWin();

	/** Сценарий при проигранном раунде */
	void RoundIsLose();
	//-------------------------------------------



	/* ---   Actions of Croupier   --- */

	/** Количество очков Крупье для текущего раунда */
	uint8 CroupiersScore = 0;
	/** Количество очков Игрока для текущего раунда */
	uint8 PlayersScore = 0;

	/** Запуск раунда */
	void StartRound();

	/** Отправить карту Крупье */
	void CardToCroupier(const bool& ibIsTurned = false);

	/** Отправить карту Игроку */
	void CardToPlayer();

	/** Обновление очков Крупье */
	void UpdateCroupiersScore();

	/** Обновление очков Игрока */
	void UpdatePlayersScore();

	/** Проверить статус раунда */
	void CheckRoundStatus();

	/** Суммирование номинала карт */
	uint8 SummarizingCards(const TArray<ERank>& iCardsData) const;
	//-------------------------------------------
};
