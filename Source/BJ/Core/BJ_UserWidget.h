#pragma once

// Base:
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// Interaction:
#include "BJ_Pawn.h"

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
	//-------------------------------------------



private:

	/* ---   Interaction with Table   --- */

	/** Текущий стол (пешка) */
	UPROPERTY(Category = Table, BlueprintReadOnly, meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true"))
	ABJ_Pawn* CurrentTable;
	//-------------------------------------------
};
