#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// Generated:
#include "BJ_PlayerController.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

class ABJ_Pawn;
//--------------------------------------------------------------------------------------



/**
 * 
 */
UCLASS()
class BJ_API ABJ_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	/* ---   Base   --- */

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//-------------------------------------------



public:

	/* ---   Initialization   --- */

	/**
	* Event для запуска инициализации Widget стола
	* @param CurrentTable - Указатель на текущий Cтол для взаимодействия в Widget
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Table-Pawn", meta = (DisplayName = "Init Widget For Table"))
	void EventInitWidgetForTable(ABJ_Pawn* CurrentTable);
	//-------------------------------------------
};
