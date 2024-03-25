// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/CSCharacterStatComponent.h"
#include "GameData/CSGameSingleton.h"

// Sets default values for this component's properties
UCSCharacterStatComponent::UCSCharacterStatComponent()
{
	CurrentLevel = 1;
	AttackRadius = 50.0f;
}


// Called when the game starts
void UCSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UCSCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UCSGameSingleton::Get().CharacterMaxLevel);
	BaseStat = UCSGameSingleton::Get().GetCharacterStat(CurrentLevel);
	check(BaseStat.MaxHp > 0.0f);
}

float UCSCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}

void UCSCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, BaseStat.MaxHp);
	
	OnHpChanged.Broadcast(CurrentHp);
}

