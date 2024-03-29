// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CSGameMode.h"
#include "Player/CSPlayerController.h"

ACSGameMode::ACSGameMode()
{
	//DefaultPawnClass 세팅
	static ConstructorHelpers::FClassFinder<APawn> ThierdPersonClssRef(TEXT("/Script/Engine.Blueprint'/Game/ArenaBattle/Blueprint/BP_CSCharacterPlayer.BP_CSCharacterPlayer_C'"));
	if (ThierdPersonClssRef.Class)
	{
		DefaultPawnClass = ThierdPersonClssRef.Class;
	}
	//PlayerControllerClass 세팅
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/UE5_ConceptSummary.CSPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
		//PlayerControllerClass = ACSPlayerController::StaticClass();            (이렇게 사용하고 싶으면 "CSPlayerController" include 해주기)

	ClearScore = 3;
	CurrentScore = 0;
	bIsCleared = false;
}

void ACSGameMode::OnPlayerScoreChanged(int32 NewPlayerScore)
{
	CurrentScore = NewPlayerScore;

	ACSPlayerController* CSPlayerController = Cast<ACSPlayerController>(GetWorld()->GetFirstPlayerController());
	if (CSPlayerController)
	{
		CSPlayerController->GameScoreChanged(CurrentScore);
	}

	if (CurrentScore >= ClearScore)
	{
		bIsCleared = true;

		if (CSPlayerController)
		{
			CSPlayerController->GameClear();
		}
	}
}

void ACSGameMode::OnPlayerdDead()
{
	ACSPlayerController* CSPlayerController = Cast<ACSPlayerController>(GetWorld()->GetFirstPlayerController());
	if (CSPlayerController)
	{
		CSPlayerController->GameOver();
	}
}

bool ACSGameMode::IsGameCleared()
{
	return bIsCleared;
}
