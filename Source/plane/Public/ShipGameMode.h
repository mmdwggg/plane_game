// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShipGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLANE_API AShipGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly);
	int Score;

	AShipGameMode();
public:
	void IncreaseScore();
};
