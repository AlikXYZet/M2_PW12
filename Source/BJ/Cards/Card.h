﻿#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// UE:
#include "Components/TextRenderComponent.h"
#include "Components/DecalComponent.h"

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



	/* ---   Components   --- */

	/** Меш визуализации карты */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CardMesh = nullptr;

	/** Текст номинала карты */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* RankText = nullptr;

	/** Декаль масти карты */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* SuitDecal = nullptr;
	//-------------------------------------------



	/* ---   Visualization   --- */

	/** Материал для масти Червей */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Playing Card|Suit Materials")
	class UMaterialInterface* HeartsMaterial = nullptr;

	/** Материал для масти Бубны */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Playing Card|Suit Materials")
	class UMaterialInterface* DiamondsMaterial = nullptr;

	/** Материал для масти Трефы */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Playing Card|Suit Materials")
	class UMaterialInterface* ClubsMaterial = nullptr;

	/** Материал для масти Пики */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Playing Card|Suit Materials")
	class UMaterialInterface* SpadesMaterial = nullptr;
	//-------------------------------------------



	/* ---   CardData   --- */

	/** Записать данные карты
	* @param	iData - Вводимые новые данные карты
	*/
	void SetCardData(const FCardData& iData);

	/** Получить данные карты */
	ERank GetCardRank();
	//-------------------------------------------



	/* ---   Card Movement   --- */

	/** Скорость перемещения */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playing Card|Movement")
	float MovementSpeed = 5.0f;

	/** Допуск отклонения */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playing Card|Movement")
	float DeviationTolerance = 0.1f;

	/**
	* Плавно переместить карту в указанную локацию
	* @param iToLocation - Точка, куда перемещается Actor карты
	*/
	void GoToLocation(const FVector& iToLocation);
	//-------------------------------------------



private:

	/* ---   CardData   --- */

	/** Данные карты (номинал и масть) */
	FCardData CardData;
	//-------------------------------------------



	/* ---   Movement   --- */

	/** Флаг контроля перемещения */
	bool bIsMovingToNewLocation = false;

	/** Новая локация к которой стремится данная карта */
	FVector NewLocation;
	//-------------------------------------------
};
