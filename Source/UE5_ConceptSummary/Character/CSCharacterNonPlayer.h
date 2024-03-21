// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CSCharacterBase.h"
#include "CSCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API ACSCharacterNonPlayer : public ACSCharacterBase
{
	GENERATED_BODY()
	
public:
	ACSCharacterNonPlayer();

protected:
	void SetDead() override;
	
};
