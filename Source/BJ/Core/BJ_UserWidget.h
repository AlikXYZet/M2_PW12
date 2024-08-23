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

	/* ---   Interaction with Table   --- */

	/** Взять карту */
	UFUNCTION(BlueprintCallable, Category = Table)
	void CommandToHit();

	/** Не брать карту */
	UFUNCTION(BlueprintCallable, Category = Table)
	void CommandToStand();

	/** Разбить руку на две (только если есть две карты и они совпали по номиналу) */
	//UFUNCTION(BlueprintCallable, Category = Table)
	//void CommandToSplit();

	/** Удвоить ставку (после этого можно получить только одну карту) */
	//UFUNCTION(BlueprintCallable, Category = Table)
	//void CommandToDouble();

	/** Сдаться (завершает раунд с проигрышем) */
	UFUNCTION(BlueprintCallable, Category = Table)
	void CommandToSurrender();

	/**
	* Event обновления очков Крупье
	* @param Score - Текущее количество очков
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = Table, meta = (DisplayName = "UpdateCroupiersScore"))
	void UpdateCroupiersScore(const uint8& Score);

	/** 
	* Event обновления очков Игрока
	* @param Score - Текущее количество очков
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = Table, meta = (DisplayName = "UpdatePlayersScore"))
	void UpdatePlayersScore(const uint8& Score);

	/** Event при раунде в ничью */
	UFUNCTION(BlueprintImplementableEvent, Category = Table, meta = (DisplayName = "RoundIsDraw"))
	void RoundIsDraw();

	/** Event при победном раунде */
	UFUNCTION(BlueprintImplementableEvent, Category = Table, meta = (DisplayName = "RoundIsWin"))
	void RoundIsWin();

	/** Event при проигранном раунде */
	UFUNCTION(BlueprintImplementableEvent, Category = Table, meta = (DisplayName = "RoundIsLose"))
	void RoundIsLose();
	//-------------------------------------------



private:

	/* ---   Interaction with Table   --- */

	/** Текущий стол (пешка) */
	UPROPERTY(BlueprintReadOnly, Category = Table, meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true"))
	class ABJ_Pawn* CurrentTable;
	//-------------------------------------------
};
