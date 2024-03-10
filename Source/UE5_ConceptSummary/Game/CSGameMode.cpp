// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CSGameMode.h"
//#include "Player/CSPlayerController.h"

ACSGameMode::ACSGameMode()
{
	//DefaultPawnClass 세팅
	//static ConstructorHelpers::FClassFinder<APawn> ThierdPersonClssRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (ThierdPersonClssRef.Class)
	//{
	//	DefaultPawnClass = ThierdPersonClssRef.Class;
	//}
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
}
