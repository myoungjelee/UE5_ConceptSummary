// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CSPlayerController.h"
#include "UI/CSHUDWidget.h"
#include "Player/CSSaveGame.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogABPlayerController);

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

	if (!UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Player0"), 0))
	{
		UE_LOG(LogABPlayerController, Error, TEXT("Save Game Error!"));
	}

	K2_OnGameRetryCount(SaveGameInstance->RetryCount);
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

	SaveGameInstance = Cast<UCSSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player0"), 0));
	if (!SaveGameInstance)
	{
		SaveGameInstance = NewObject<UCSSaveGame>();
		SaveGameInstance->RetryCount = 0;
	}
	SaveGameInstance->RetryCount++;

	K2_OnGameRetryCount(SaveGameInstance->RetryCount);
}
