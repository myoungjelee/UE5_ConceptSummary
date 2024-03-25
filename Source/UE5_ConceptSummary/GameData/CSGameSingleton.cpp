// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/CSGameSingleton.h"

DEFINE_LOG_CATEGORY(LogCSGameSingleton);

UCSGameSingleton::UCSGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/ArenaBattle/GameData/CSCharacterStatTable.CSCharacterStatTable'"));
	if (DataTableRef.Object != nullptr)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FCSCharacterStat*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0);
}

UCSGameSingleton& UCSGameSingleton::Get()
{
	// TODO: insert return statement here
	UCSGameSingleton* Singleton = CastChecked< UCSGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogCSGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UCSGameSingleton>();
}
