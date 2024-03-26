// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/CSCharacterStat.h"
#include "CSCharacterStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API UCSCharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	void UpdateStat(const FCSCharacterStat& BaseStat, const FCSCharacterStat& ModifierStat);

private:
	UPROPERTY()
	TMap<FName, class UTextBlock*> BaseLookup;

	UPROPERTY()
	TMap<FName, class UTextBlock*> ModifierLookup;
};
