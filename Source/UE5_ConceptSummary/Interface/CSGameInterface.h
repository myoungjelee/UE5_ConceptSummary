// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CSGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCSGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE5_CONCEPTSUMMARY_API ICSGameInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnPlayerScoreChanged(int32 NewPlayerScore) = 0;
	virtual void OnPlayerdDead() = 0;
	virtual bool IsGameCleared() = 0;
};
