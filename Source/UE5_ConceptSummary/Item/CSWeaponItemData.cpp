// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CSWeaponItemData.h"


FPrimaryAssetId UCSWeaponItemData::GetPrimaryAssetId() const
{
    Super::GetPrimaryAssetId();

    return FPrimaryAssetId("CSItemData", GetFName());
}
