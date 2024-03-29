// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSUserWidget.h"
#include "GameData/CSCharacterStat.h"
#include "CSHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API UCSHpBarWidget : public UCSUserWidget
{
	GENERATED_BODY()
	
public:
	UCSHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	//FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateStat(const FCSCharacterStat& BaseStat, const FCSCharacterStat& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);
	FString GetHpStatText();

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> HpStat;

	UPROPERTY()
	float CurrentHp;

	UPROPERTY()
	float MaxHp;
};
