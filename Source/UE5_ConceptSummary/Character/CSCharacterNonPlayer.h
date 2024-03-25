// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CSCharacterBase.h"
#include "Engine/StreamableManager.h"
#include "Interface/CSCharacterAIInterface.h"
#include "CSCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS(config=ConceptSummary)
class UE5_CONCEPTSUMMARY_API ACSCharacterNonPlayer : public ACSCharacterBase, public ICSCharacterAIInterface
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

// AI Section
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void AttackByAI() override;
	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;

	FAICharacterAttackFinished OnAttackFinished;

	virtual void NotifyComboActionEnd() override;
};
