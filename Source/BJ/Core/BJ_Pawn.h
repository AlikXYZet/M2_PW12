#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Interaction:
#include "BJ/Cards/CardStruct.h"

// Generated:
#include "BJ_Pawn.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

class UCameraComponent;
class ACard;
class ADeck;
class UBJ_UserWidget;
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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TableMesh = nullptr;

	/** Точка местоположения Колоды */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DeckLocationPoint = nullptr;

	/** Точка местоположения карт Крупье */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* CroupierCardsLocationPoint = nullptr;

	/** Точка местоположения карт Игрока */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* PlayerCardsLocationPoint = nullptr;
	//-------------------------------------------



	/* ---   Camera   --- */

	/** Камера Игрока */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;
	//-------------------------------------------



	/* ---   Cards and Deck   --- */

	// Экземпляр карты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = "Deck of Cards")
	TSubclassOf<ACard> CardsType = nullptr;

	// Трансформ карт
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck of Cards")
	FVector CardsScale = FVector(0.1f);

	// Экземпляр колоды
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = "Deck of Cards")
	TSubclassOf<ADeck> DeckType = nullptr;

	// Трансформ карт
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck of Cards")
	FVector DeckScale = FVector(0.1f);
	//-------------------------------------------



	/* ---   Interaction from Widget   --- */

	/** Запуск раунда */
	void StartRound();

	/** Взять карту */
	void WidgetCommandToHit();

	/** Не брать карту */
	void WidgetCommandToStand();

	/** Разбить руку на две (только если есть две карты и они совпали по номиналу) */
	//void CommandToSplit();

	/** Удвоить ставку (после этого можно получить только одну карту) */
	//void CommandToDouble();

	/** Сдаться (завершает раунд с проигрышем) */
	void WidgetCommandToSurrender();

	/** Функция сохранения указателя на Widget стола
	* (необходим для прямой передачи данных от Стола к Виджету)
	* @param iCurrentUserWidget - Указатель на текущий Widget стола
	*/
	void InitTableForWidget(UBJ_UserWidget* iCurrentUserWidget);
	//-------------------------------------------



private:

	/* ---   Cards and Deck   --- */

	/** Указатель на колоду карт */
	ADeck* pDeck;

	/** Разыгранные карты Крупье за текущий раунд */
	TArray<ACard*> CroupierCards;
	/** Разыгранные карты Игрока за текущий раунд */
	TArray<ACard*> PlayerCards;

	/** Ширина карты */
	float WidthOfCard;

	/** Очистить стол от карт колоды (сбросить раунд) */
	void ClearOfCards();

	/** Переместить все карты "Руки" для лучшего обзора
	* @param	iPoint - Точка местоположения чего-либо в виде " USceneComponent* "
	* @param	iCards - Массив карт "Руки" для переставления их на столе
	*/
	void MoveAllCards(const USceneComponent* iPoint, TArray<ACard*>& iCards);

	/** Пересчёт Трансформы (+Локациия, +Ротации и замена размера)
	* @param	iPoint - Точка местоположения чего-либо в виде " USceneComponent* "
	* @param	iSetTransform - Трасформация обьекта относительно " iPoint "
	* @return	Расчитанная Трансформация
	*/
	FTransform ConversionTransform(const USceneComponent* iPoint, const FVector& iSetScale);

	/** Создание и перемещение новой Карты
	* @param	iCards - Массив карт "Руки" для добавления в него новой Карты
	* @return	Указатель на новую Карту
	*/
	ACard* CreateNewCard(TArray<ACard*>& iCards);
	//-------------------------------------------



	/* ---   Interaction from Widget   --- */

	/** Указатель на текущий виджет */
	UBJ_UserWidget* pCurrentUserWidget = nullptr;

	/** Флаг контроля блокировки команд */
	bool bIsBlockCommands = true;
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

	/** Карты Крупье собраны */
	bool bCroupierCardsIsCollected = false;

	/** Отправить карту Крупье */
	void CardToCroupier();

	/** Отправить карту Игроку */
	void CardToPlayer();

	/** Обновление очков Крупье */
	void UpdateCroupiersScore();

	/** Обновление очков Игрока */
	void UpdatePlayersScore();

	/** Проверить статус раунда */
	void CheckRoundStatus();

	/** Итогово проверить статус раунда (с окончательным результатом) */
	void FinallyCheckRoundStatus();

	/** Суммирование номинала карт (расчёт количества очков "Руки")
	* @param	iCards - Массив указателей на карты "Руки", которую требуется расчитать
	* @return	Количество очков данной "Руки"
	*/
	uint8 SummarizingCards(const TArray<ACard*>& ipCards) const;
	//-------------------------------------------
};
