// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/CSCharacterStat.h"
#include "CSHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API UCSHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCSHUDWidget(const FObjectInitializer& ObjectInitializer);

	void UpdateStat(const FCSCharacterStat& BaseStat, const FCSCharacterStat& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UCSHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UCSCharacterStatWidget> CharacterStat;
};
