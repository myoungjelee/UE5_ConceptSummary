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
