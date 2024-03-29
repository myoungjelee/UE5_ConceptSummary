// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CSHUDWidget.h"
#include "UI/CSHpBarWidget.h"
#include "UI/CSCharacterStatWidget.h"
#include "Interface/CSCharacterHUDInterface.h"

UCSHUDWidget::UCSHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCSHUDWidget::UpdateStat(const FCSCharacterStat& BaseStat, const FCSCharacterStat& ModifierStat)
{
	FCSCharacterStat TotalStat = BaseStat + ModifierStat;
	HpBar->UpdateStat(BaseStat, ModifierStat);
	CharacterStat->UpdateStat(BaseStat, ModifierStat);
}

void UCSHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UCSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UCSHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	CharacterStat = Cast<UCSCharacterStatWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ensure(CharacterStat);

	ICSCharacterHUDInterface* HUDPawn = Cast<ICSCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}
}
