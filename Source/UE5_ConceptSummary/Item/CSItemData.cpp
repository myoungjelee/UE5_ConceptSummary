// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CSItemData.h"

FPrimaryAssetId UCSItemData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("CSItemData", GetFName());
}
