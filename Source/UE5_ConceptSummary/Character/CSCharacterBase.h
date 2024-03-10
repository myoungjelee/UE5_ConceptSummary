// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class UE5_CONCEPTSUMMARY_API ACSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSCharacterBase();

protected:
	virtual void SetCharacterControlData(const class UCSCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta =(AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UCSCharacterControlData*> CharacterControlManager;

// Combo Action Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack" , Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCSComboActionData> ComboActionData;
	
	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
    FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;
};
