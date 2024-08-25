#pragma once

// Base:
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// Generated:
#include "BJ_UserWidget.generated.h"



/**
 *
 */
UCLASS()
class BJ_API UBJ_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/* ---   Base   --- */

	//~UBJ_UserWidget();

	// Аналогичен простому Construct()
	virtual void NativeConstruct() override;

	// Аналогичен простому Tick(")
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	//--------------------------------------------



	/* ---   Interaction with Table   --- */

	/** Взять карту */
	UFUNCTION(BlueprintCallable, Category = "Table-Pawn")
	void CommandToHit();

	/** Не брать карту */
	UFUNCTION(BlueprintCallable, Category = "Table-Pawn")
	void CommandToStand();

	/** Разбить руку на две (только если есть две карты и они совпали по номиналу) */
	//UFUNCTION(BlueprintCallable, Category = Table)
	//void CommandToSplit();

	/** Удвоить ставку (после этого можно получить только одну карту) */
	//UFUNCTION(BlueprintCallable, Category = Table)
	//void CommandToDouble();

	/** Сдаться (завершает раунд с проигрышем) */
	UFUNCTION(BlueprintCallable, Category = "Table-Pawn")
	void CommandToSurrender();

	/** Запустить новый раунд
	*
	* @warning	Может сразу вызвать одну из " Event Notice Round Is *** "
	*/
	UFUNCTION(BlueprintCallable, Category = "Table-Pawn")
	void CommandToNextRound();

	/**
	* Event обновления очков Крупье
	* @param Score - Текущее количество очков
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Table-Pawn", meta = (DisplayName = "Update Croupiers Score"))
	void EventUpdateCroupiersScore(const uint8& Score);

	/**
	* Event обновления очков Игрока
	* @param Score - Текущее количество очков
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Table-Pawn", meta = (DisplayName = "Update Players Score"))
	void EventUpdatePlayersScore(const uint8& Score);

	/** Event при раунде в ничью */
	UFUNCTION(BlueprintImplementableEvent, Category = "Table-Pawn", meta = (DisplayName = "Notice Round Is Draw"))
	void EventNoticeRoundIsDraw();

	/** Event при победном раунде */
	UFUNCTION(BlueprintImplementableEvent, Category = "Table-Pawn", meta = (DisplayName = "Notice Round Is Win"))
	void EventNoticeRoundIsWin();

	/** Event при проигранном раунде */
	UFUNCTION(BlueprintImplementableEvent, Category = "Table-Pawn", meta = (DisplayName = "Notice Round Is Lose"))
	void EventNoticeRoundIsLose();
	//-------------------------------------------



private:

	/* ---   Interaction with Table   --- */

	/** Текущий стол (пешка) */
	UPROPERTY(BlueprintReadOnly, Category = "Table-Pawn", meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true"))
	class ABJ_Pawn* CurrentTable;
	//-------------------------------------------
};
