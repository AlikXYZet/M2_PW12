#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// Generated:
#include "BJ_PlayerController.generated.h"

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
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InitWidgetForTable"))
	void InitWidgetForTable(class ABJ_Pawn* CurrentTable);
	//-------------------------------------------
};
