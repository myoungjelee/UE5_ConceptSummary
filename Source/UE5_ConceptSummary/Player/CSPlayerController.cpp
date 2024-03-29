// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CSPlayerController.h"
#include "UI/CSHUDWidget.h"


ACSPlayerController::ACSPlayerController()
{
	static ConstructorHelpers::FClassFinder<UCSHUDWidget> CSHUDWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ArenaBattle/UI/WBp_CSHUD.WBp_CSHUD_C'"));
	if (CSHUDWidgetRef.Class)
	{
		CSHUDWidgetClass = CSHUDWidgetRef.Class;
	}
}

void ACSPlayerController::GameScoreChanged(int32 NewScore)
{
	K2_OnScoreChanged(NewScore);
}

void ACSPlayerController::GameOver()
{
	K2_OnGameOver();
}

void ACSPlayerController::GameClear()
{
	K2_OnGameClear();
}

void ACSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	CSHUDWidget = CreateWidget<UCSHUDWidget>(this, CSHUDWidgetClass);
	if (CSHUDWidget)
	{
		CSHUDWidget->AddToViewport();
	}
}
