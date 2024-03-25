// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CSAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API ACSAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACSAIController();

	void RunAI();
	void StopAi();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
