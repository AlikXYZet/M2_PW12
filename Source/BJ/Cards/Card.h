#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// UE:
#include "Components/BoxComponent.h"
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

	ACard(const FCardData& iCardData);
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



private:

	/* ---   CardData   --- */
	// Данные карты (номинал и масть)
	FCardData CardData;
	//-------------------------------------------
};
