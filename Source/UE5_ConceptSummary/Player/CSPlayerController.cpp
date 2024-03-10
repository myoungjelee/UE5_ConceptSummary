// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CSPlayerController.h"

void ACSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
