#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// UE:
#include "Components/TextRenderComponent.h"

// Interaction:
#include "CardStruct.h"

// Generated:
#include "Card.generated.h"



UCLASS()
class BJ_API ACard : public AActor
{
	GENERATED_BODY()

public:

	/* ---   Constructors   --- */

	// Sets default values for this actor's properties
	ACard();
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

	// Меш визуализации карты
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CardMesh = nullptr;
	// Текст номинала карты
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* RankText = nullptr;
	// Текст масти карты
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* SuitText = nullptr;
	//-------------------------------------------



	/* ---   CardData   --- */

	// Записать данные карты
	void SetCardData(const FCardData& iData);
	// Получить данные карты
	ERank GetCardRank();
	//-------------------------------------------



	/* ---   Movement   --- */

	// Скорость перемещения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MovementSpeed = 5.0f;

	// Допуск отклонения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float DeviationTolerance = 0.1f;

	// Флаг контроля перемещения
	bool bIsMovingToNewLocation = false;

	/**
	* Плавно переместить карту в указанную локацию
	* @param iToLocation - Точка, куда перемещается Actor карты
	*/
	void GoToLocation(const FVector& iToLocation);
	//-------------------------------------------



private:

	/* ---   CardData   --- */
	// Данные карты (номинал и масть)
	FCardData CardData;
	//-------------------------------------------



	/* ---   Movement   --- */
	// Новая локация к которой стремится данная карта
	FVector NewLocation;
	//-------------------------------------------
};
