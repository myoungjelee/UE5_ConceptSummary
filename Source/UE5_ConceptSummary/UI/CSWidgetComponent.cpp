// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CSWidgetComponent.h"
#include "CSUserWidget.h"

void UCSWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UCSUserWidget* CSUserWidget = Cast<UCSUserWidget>(GetWidget());
	if (CSUserWidget)
	{
		CSUserWidget->SetOwningActor(GetOwner());
	}
}
