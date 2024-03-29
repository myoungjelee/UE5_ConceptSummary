// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/CSItemData.h"
#include "CSPotionItemData.generated.h"

/**
 *
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API UCSPotionItemData : public UCSItemData
{
	GENERATED_BODY()

public:
	UCSPotionItemData();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("CSItemData", GetFName());
	}

	UPROPERTY(EditAnywhere, Category = Hp)
	float HealAmount;
};
