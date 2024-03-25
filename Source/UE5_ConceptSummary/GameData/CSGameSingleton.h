// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameData/CSCharacterStat.h"
#include "CSGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCSGameSingleton, Error, All);

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API UCSGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UCSGameSingleton();
	static UCSGameSingleton& Get();

// Character Stat Data Section
public:
	FORCEINLINE FCSCharacterStat GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FCSCharacterStat(); }

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FCSCharacterStat> CharacterStatTable;
};
