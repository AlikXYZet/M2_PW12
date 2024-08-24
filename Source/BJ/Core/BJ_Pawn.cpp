// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "BJ_Pawn.h"

// Interaction:
#include "BJ_PlayerController.h"
#include "BJ/Cards/Deck.h"
#include "BJ_UserWidget.h"



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
	CroupierCardsLocationPoint->SetRelativeLocation(FVector(10.f, 0.f, 70.f));

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

	// Проверка на наличие корректной Колоды
	pDeck = Cast<ADeck>(DeckActor->GetChildActor());
	if (!pDeck)
	{
		UE_LOG(LogTemp, Error, TEXT("ABJ_Pawn %s : DeckActor is NOT ADeck"), *GetNameSafe(this));
	}

	StartRound();
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

	// Инициализация Виджета стола при подключении игрока к пешке
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
	CardToPlayer();
	CroupierTurn();
}

void ABJ_Pawn::CommandToStand()
{
	CroupierTurn();
}

void ABJ_Pawn::CommandToSurrender()
{
	RoundIsLose();
	// PS: Временно! 
	// Следует сделать подтверждение данного сценария через Виджет
}

void ABJ_Pawn::InitTableForWidget(UBJ_UserWidget* iCurrentUserWidget)
{
	pCurrentUserWidget = iCurrentUserWidget;
}
//--------------------------------------------------------------------------------------



/* ---   Game Status   --- */

void ABJ_Pawn::CroupierTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("BJ_Pawn::CroupierTurn"));
}

void ABJ_Pawn::RoundIsDraw()
{
	UE_LOG(LogTemp, Warning, TEXT("BJ_Pawn::RoundIsDraw"));

	pCurrentUserWidget->RoundIsDraw();
}

void ABJ_Pawn::RoundIsWin()
{
	UE_LOG(LogTemp, Warning, TEXT("BJ_Pawn::RoundIsWin"));

	pCurrentUserWidget->RoundIsWin();
}

void ABJ_Pawn::RoundIsLose()
{
	UE_LOG(LogTemp, Warning, TEXT("BJ_Pawn::RoundIsLose"));

	pCurrentUserWidget->RoundIsLose();
}
//--------------------------------------------------------------------------------------



/* ---   Actions of Croupier   --- */

void ABJ_Pawn::StartRound()
{
	// Проверка при разных сценариях
	if (pDeck && pCurrentUserWidget)
	{
		pDeck->ClearOfCards();

		// Первоначальная раздача по две карты
		CardToCroupier();
		CardToPlayer();
		CardToCroupier();
		CardToPlayer();
	}
	else if (!pDeck)
	{
		UE_LOG(LogTemp, Error, TEXT("ABJ_Pawn::StartRound : pDeck is NULLPTR"));

		/* PS: Если работает "автоподхват игрока" в данную пешку,
		* то InitTableForWidget() выполняется раньше, чем BeginPlay().
		*
		* Следовательно pDeck = nullptr,
		* а StartRound() в BeginPlay() не выполнит работу
		*/
	}
	else if (!pCurrentUserWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("ABJ_Pawn::StartRound : pCurrentUserWidget is NULLPTR"));

		/* PS: Если работает "вход игрока" в данную пешку,
		* то BeginPlay() выполняется раньше, чем InitTableForWidget().
		*
		* Следовательно pCurrentUserWidget = nullptr,
		* а StartRound() в InitTableForWidget() не выполнит работу
		*/
	}
}

void ABJ_Pawn::CardToCroupier(const bool& ibIsTurned)
{
	FCardData lNewCard = pDeck->TakeUpperCard(CroupierCardsLocationPoint->GetComponentLocation());

	float lSpaceY = 10 * pDeck->DeckMesh->GetRelativeScale3D().Y;

	CroupierCardsLocationPoint->AddRelativeLocation(FVector(0.f, -lSpaceY, 0.f));

	CroupiersCards.Add(lNewCard);

	UpdateCroupiersScore();
	CheckRoundStatus();
}

void ABJ_Pawn::CardToPlayer()
{
	FCardData lNewCard = pDeck->TakeUpperCard(PlayerCardsLocationPoint->GetComponentLocation());

	PlayersCards.Add(lNewCard);

	UpdatePlayersScore();
	CheckRoundStatus();
}

void ABJ_Pawn::UpdateCroupiersScore()
{
	// Счёт Крупье: расчёт и обновление данных
	CroupiersScore = SummarizingCards(CroupiersCards);
	pCurrentUserWidget->UpdateCroupiersScore(CroupiersScore);
}

void ABJ_Pawn::UpdatePlayersScore()
{
	// Счёт Игрока: расчёт и обновление данных
	PlayersScore = SummarizingCards(PlayersCards);
	pCurrentUserWidget->UpdatePlayersScore(PlayersScore);
}

void ABJ_Pawn::CheckRoundStatus()
{
	if (CroupiersScore == PlayersScore && CroupiersScore == 21) // Проверка "Ничья"
	{
		pCurrentUserWidget->RoundIsDraw();
	}
	else if (PlayersScore == 21 || CroupiersScore > 21) // Проверка "Победа"
	{
		pCurrentUserWidget->RoundIsWin();
	}
	else if (CroupiersScore == 21 || PlayersScore > 21) // Проверка "Поражение"
	{
		pCurrentUserWidget->RoundIsLose();
	}
}

uint8 ABJ_Pawn::SummarizingCards(const TArray<FCardData> iCards) const
{
	// Счётчик количества Тузов
	uint8 lNumAces = 0;

	uint8 lResult = 0;

	// Получение максимального Счёта
	for (const FCardData& Data : iCards)
	{
		if (uint8(Data.Rank) > 10) // Проверка "Картинки"
		{
			lResult += 10;
		}
		else if (Data.Rank == ERank::Ace) // Проверка "Туза"
		{
			lResult += 11;
			++lNumAces;
		}
		else
		{
			lResult += uint8(Data.Rank);
		}
	}

	// Получение максимального Счёта с учётом всех Тузов, но не больше 21
	while (lResult > 21 && lNumAces)
	{
		lResult -= 10; // Туз либо =11, либо =1
		--lNumAces;
	}

	return lResult;
}
//--------------------------------------------------------------------------------------
