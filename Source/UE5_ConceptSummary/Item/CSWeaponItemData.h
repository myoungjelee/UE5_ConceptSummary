// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/CSItemData.h"
#include "CSWeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CONCEPTSUMMARY_API UCSWeaponItemData : public UCSItemData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	//TObjectPtr<USkeletalMesh> WeaponMesh;
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;
};
