// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "BJ_Pawn.h"

// Interaction:
#include "BJ_PlayerController.h"



/* ---   Constructors   --- */

// Sets default values
ABJ_Pawn::ABJ_Pawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Предварительно

	// Автоподхват игрока
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// Warning: Данный способ дважды ввызывает PossessedBy(*)

	

	/* ---   Visualization   --- */

	// Корневой компонент
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	TableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Table Mesh"));
	TableMesh->SetupAttachment(RootComponent);

	DeckActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Deck Actor"));
	DeckActor->SetupAttachment(RootComponent);
	DeckActor->SetRelativeLocation(FVector(20.f, -30.f, 70.3f));
	DeckActor->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

	CroupierCardsLocationPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Croupier Cards"));
	CroupierCardsLocationPoint->SetupAttachment(RootComponent);
	CroupierCardsLocationPoint->SetRelativeLocation(FVector(0.f, 0.f, 70.f));

	PlayerCardsLocationPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Player Cards"));
	PlayerCardsLocationPoint->SetupAttachment(RootComponent);
	PlayerCardsLocationPoint->SetRelativeLocation(FVector(42.f, 0.f, 70.3f));

	//-------------------------------------------


	/* ---   Camera   --- */

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(60.f, 0.f, 120.f));
	Camera->SetRelativeRotation(FRotator(-60.f, 180.f, 0.f));
	//-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

// Called when the game starts or when spawned
void ABJ_Pawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABJ_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABJ_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABJ_Pawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ABJ_PlayerController* lCurrentPCTable = Cast<ABJ_PlayerController>(NewController);

	if (lCurrentPCTable)
	{
		lCurrentPCTable->InitWidgetForTable(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ABJ_Pawn::PossessedBy : NewController is NOT ABJ_PlayerController"));
	}
}

void ABJ_Pawn::UnPossessed()
{
	Super::UnPossessed();
}
//--------------------------------------------------------------------------------------



/* ---   Interaction from Widget   --- */

void ABJ_Pawn::CommandToHit()
{
	UE_LOG(LogTemp, Warning, TEXT("BJ_Pawn::CommandToHit"));
}

void ABJ_Pawn::CommandToStand()
{
	UE_LOG(LogTemp, Warning, TEXT("BJ_Pawn::CommandToStand"));
}

void ABJ_Pawn::CommandToSurrender()
{
	UE_LOG(LogTemp, Warning, TEXT("BJ_Pawn::CommandToSurrender"));
}
//--------------------------------------------------------------------------------------