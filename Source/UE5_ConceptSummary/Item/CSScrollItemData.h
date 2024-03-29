// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/CSItemData.h"
#include "GameData/CSCharacterStat.h"
#include "CSScrollItemData.generated.h"

/**
 *
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API UCSScrollItemData : public UCSItemData
{
	GENERATED_BODY()

public:
	UCSScrollItemData();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("CSItemData", GetFName());
	}

	UPROPERTY(EditAnywhere, Category = Stat)
	FCSCharacterStat BaseStat;
};
