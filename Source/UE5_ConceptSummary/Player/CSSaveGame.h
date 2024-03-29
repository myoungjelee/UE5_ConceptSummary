// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API UCSSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UCSSaveGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game)
	int32 RetryCount;
};
