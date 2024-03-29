// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/CSGameInterface.h"
#include "CSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API ACSGameMode : public AGameModeBase, public ICSGameInterface
{
	GENERATED_BODY()
	
public:
	ACSGameMode();

	virtual void OnPlayerScoreChanged(int32 NewPlayerScore) override;
	virtual void OnPlayerdDead() override;
	virtual bool IsGameCleared() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = Game)
	int32 ClearScore;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game)
	int32 CurrentScore;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game)
	uint8 bIsCleared : 1;
};
