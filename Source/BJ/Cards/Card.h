#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CardStruct.h"

#include "Card.generated.h"

UCLASS()
class BJ_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
