// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CSCharacterBase.h"
#include "Engine/StreamableManager.h"
#include "CSCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS(config=ConceptSummary)
class UE5_CONCEPTSUMMARY_API ACSCharacterNonPlayer : public ACSCharacterBase
{
	GENERATED_BODY()
	
public:
	ACSCharacterNonPlayer();

	virtual void PostInitializeComponents() override;
protected:
	void SetDead() override;
	void NPCMeshLoadCompleted();
	
	UPROPERTY(config)
	TArray<FSoftObjectPath> NPCMeshes;

	TSharedPtr<FStreamableHandle> NPCMeshHandle;
};
