// Fill out your copyright notice in the Description page of Project Settings.

// Base:
#include "BJ_Pawn.h"

// UE:
#include "Camera/CameraComponent.h"

// Interaction:
#include "BJ_PlayerController.h"
#include "BJ/Cards/Deck.h"
#include "BJ/Cards/Card.h"
#include "BJ_UserWidget.h"
//--------------------------------------------------------------------------------------



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

	DeckLocationPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Deck Actor"));
	DeckLocationPoint->SetupAttachment(RootComponent);
	DeckLocationPoint->SetRelativeLocation(FVector(20.f, -30.f, 70.3f));

	CroupierCardsLocationPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Croupier Cards"));
	CroupierCardsLocationPoint->SetupAttachment(RootComponent);
	CroupierCardsLocationPoint->SetRelativeLocation(FVector(10.f, 0.f, 70.3f));

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

	// Проверка на корректность и создание Колоды
	if (DeckType.Get())
	{
		pDeck = GetWorld()->SpawnActor<ADeck>(
			DeckType.Get(),
			ConversionTransform(DeckLocationPoint, DeckScale));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ADeck %s : DeckType is NOT specified"), *GetNameSafe(this));
	}

	// Проверка на корректность типа Карт
	if (!CardsType.Get())
	{
		UE_LOG(LogTemp, Error, TEXT("ADeck %s : CardsType is NOT specified"), *GetNameSafe(this));
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
		lCurrentPCTable->EventInitWidgetForTable(this);
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



/* ---   Cards and Deck   --- */

void ABJ_Pawn::ClearOfCards()
{
	// Удаление Карт Крупье
	for (ACard* pCard : CroupierCards)
	{
		pCard->Destroy();
	}
	CroupierCards.Empty();

	// Удаление Карт Игрока
	for (ACard* pCard : PlayerCards)
	{
		pCard->Destroy();
	}
	PlayerCards.Empty();

	// Сброс флагов раунда
	bCroupierCardsIsCollected = false;
	bIsBlockCommands = false;

	// Сброс колоды при количестве карт меньше 16
	if (pDeck->GetNumOfCards() < 16)
	{
		pDeck->Reset();
		// PS: максимальное количество разыгранных карт
		// за раунд при ОДНОЙ колоде = 16
	}
}

void ABJ_Pawn::MoveAllCards(const USceneComponent* iPoint, TArray<ACard*>& iCards)
{
	if (iCards.Num() > 0)
	{
		if (!WidthOfCard)
		{
			WidthOfCard = 100.f * iCards[0]->CardMesh->GetComponentScale().Y;
		}

		int32 lNumCards = iCards.Num();

		// Расчитанный промежуток между картами + ширина между картами
		float lSpace = WidthOfCard + WidthOfCard / 16;
		// Расчитанная половина длины от середин первой и последней карты
		float lWidthAllCards = lSpace * (lNumCards - 1) / 2;

		for (int32 i = 0; i < lNumCards; ++i)
		{
			// Расчёт необходимой локации
			FVector lCalculatedLocation
				= iPoint->GetComponentLocation()
				+ iPoint->GetComponentRotation().RotateVector(
					FVector(
						0.f,
						lWidthAllCards - i * (lSpace),
						0.f));

			iCards[i]->GoToLocation(lCalculatedLocation);
		}
	}
}

FTransform ABJ_Pawn::ConversionTransform(const USceneComponent* iPoint, const FVector& iSetScale)
{
	FTransform lResult = iPoint->GetComponentTransform();

	lResult.SetScale3D(iSetScale);

	//UE_LOG(LogTemp, Warning, TEXT("ABJ_Pawn::ConversionTransform : %s"), *lResult.ToString());

	return lResult;
}

ACard* ABJ_Pawn::CreateNewCard(TArray<ACard*>& iCards)
{
	// Создать "взятую" карту и переместить её к владельцу
	ACard* pNewCard = GetWorld()->SpawnActor<ACard>(
		CardsType.Get(),
		ConversionTransform(DeckLocationPoint, DeckScale));

	pNewCard->SetCardData(pDeck->TakeUpperCard());

	iCards.Add(pNewCard);

	return pNewCard;
}
//--------------------------------------------------------------------------------------



/* ---   Interaction from Widget   --- */

void ABJ_Pawn::StartRound()
{
	// Проверка при разных сценариях
	if (pDeck && pCurrentUserWidget && bIsBlockCommands)
	{
		ClearOfCards();

		// Сперва: Раздать карты без проверки количества очков
		CardToCroupier();
		CardToPlayer();
		CardToCroupier();
		CardToPlayer();

		// После: Проверить количество очков
		UpdateCroupiersScore();
		UpdatePlayersScore();
		CheckRoundStatus();
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
	else if (!bIsBlockCommands)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABJ_Pawn::StartRound : Round is running"));

		// PS: Раунд нельзя перезапустить до его окончания
	}
}

void ABJ_Pawn::WidgetCommandToHit()
{
	if (!bIsBlockCommands)
	{
		CardToPlayer();
		UpdatePlayersScore();
		CheckRoundStatus();

		CroupierTurn();
	}
}

void ABJ_Pawn::WidgetCommandToStand()
{
	if (!bIsBlockCommands)
	{
		CroupierTurn();

		if (bCroupierCardsIsCollected)
		{
			FinallyCheckRoundStatus();
		}
	}
}

void ABJ_Pawn::WidgetCommandToSurrender()
{
	if (!bIsBlockCommands)
	{
		RoundIsLose();
		// PS: Временно! 
		// Следует сделать подтверждение данного сценария через Виджет
	}
}

void ABJ_Pawn::InitTableForWidget(UBJ_UserWidget* iCurrentUserWidget)
{
	pCurrentUserWidget = iCurrentUserWidget;
}
//--------------------------------------------------------------------------------------



/* ---   Game Status   --- */

void ABJ_Pawn::CroupierTurn()
{
	// Проверка хода Игрока
	if (!bIsBlockCommands)
	{
		// Собирать карты, пока очков менее 16
		if (CroupiersScore <= 16)
		{
			CardToCroupier();
			UpdateCroupiersScore();
		}
		else if (!bCroupierCardsIsCollected)
		{
			bCroupierCardsIsCollected = true;
		}

		CheckRoundStatus();
	}
}

void ABJ_Pawn::RoundIsDraw()
{
	bIsBlockCommands = true;
	pCurrentUserWidget->EventNoticeRoundIsDraw();
}

void ABJ_Pawn::RoundIsWin()
{
	bIsBlockCommands = true;
	pCurrentUserWidget->EventNoticeRoundIsWin();
}

void ABJ_Pawn::RoundIsLose()
{
	bIsBlockCommands = true;
	pCurrentUserWidget->EventNoticeRoundIsLose();
}
//--------------------------------------------------------------------------------------



/* ---   Actions of Croupier   --- */

void ABJ_Pawn::CardToCroupier()
{
	// Запомнить новую карту и передать её Крупье
	ACard* lCard = CreateNewCard(CroupierCards);

	MoveAllCards(CroupierCardsLocationPoint, CroupierCards);
}

void ABJ_Pawn::CardToPlayer()
{
	// Запомнить новую карту и передать её Игроку
	ACard* lCard = CreateNewCard(PlayerCards);

	MoveAllCards(PlayerCardsLocationPoint, PlayerCards);
}

void ABJ_Pawn::UpdateCroupiersScore()
{
	// Счёт Крупье: расчёт и обновление данных
	CroupiersScore = SummarizingCards(CroupierCards);
	pCurrentUserWidget->EventUpdateCroupiersScore(CroupiersScore);
}

void ABJ_Pawn::UpdatePlayersScore()
{
	// Счёт Игрока: расчёт и обновление данных
	PlayersScore = SummarizingCards(PlayerCards);
	pCurrentUserWidget->EventUpdatePlayersScore(PlayersScore);
}

void ABJ_Pawn::CheckRoundStatus()
{
	// PS: В первую очередь проверяем "Ничью" при 21, так как могут сработать другие варианты
	if (CroupiersScore == PlayersScore && CroupiersScore == 21) // Проверка на "Ничью" при 21 (найменее вероятно)
	{
		RoundIsDraw();
	}
	else if (PlayersScore > 21 || CroupiersScore == 21) // Проверка на "Поражение" (найболее вероятно)
	{
		RoundIsLose();
	}
	else if (CroupiersScore > 21 || PlayersScore == 21) // Проверка на "Победу"
	{
		RoundIsWin();
	}
}

void ABJ_Pawn::FinallyCheckRoundStatus()
{
	if (CroupiersScore > PlayersScore) // Проверка на "Поражение" (найболее вероятно)
	{
		RoundIsLose();
	}
	else if (PlayersScore > CroupiersScore) // Проверка на "Победу"
	{
		RoundIsWin();
	}
	else if (CroupiersScore == PlayersScore) // Проверка на "Ничью" (найменее вероятно)
	{
		RoundIsDraw();
	}
}

uint8 ABJ_Pawn::SummarizingCards(const TArray<ACard*>& ipCards) const
{
	uint8 lResult = 0;

	// Счётчик количества Тузов
	uint8 lNumAces = 0;

	// Счётчик количества Тузов
	ERank lCardRank;

	// Получение максимального Счёта
	for (const ACard* Data : ipCards)
	{
		lCardRank = Data->GetCardRank();

		if (uint8(lCardRank) > 10) // Проверка "Картинки"
		{
			lResult += 10;
		}
		else if (lCardRank == ERank::Ace) // Проверка "Туза"
		{
			lResult += 11;
			++lNumAces;
		}
		else
		{
			lResult += uint8(lCardRank);
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
