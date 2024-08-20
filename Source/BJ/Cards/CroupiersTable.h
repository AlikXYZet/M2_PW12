#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// UE:
#include "Components/ChildActorComponent.h"
#include "Camera/CameraComponent.h"

// Interaction:
#include "Deck.h"

// Generated:
#include "CroupiersTable.generated.h"



UCLASS()
class BJ_API ACroupiersTable : public APawn
{
	GENERATED_BODY()

public:
	/* ---   Constructors   --- */

	// Sets default values for this pawn's properties
	ACroupiersTable();
	//-------------------------------------------



	/* ---   Base   --- */

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//-------------------------------------------



	/* ---   Visualization   --- */

	// Меш визуализации стола
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TableMesh = nullptr;
	// Колода карт
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* DeckActor;

	// Точка местоположения карт Крупье
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CroupierCardsLocationPoint = nullptr;
	// Точка местоположения карт Игрока
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* PlayerCardsLocationPoint = nullptr;
	//-------------------------------------------



	/* ---   Camera   --- */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;
	//-------------------------------------------
};
