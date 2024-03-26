// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API ACSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACSPlayerController();
	
protected:
	virtual void BeginPlay() override;

// HUD Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UCSHUDWidget> CSHUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UCSHUDWidget> CSHUDWidget;
};
