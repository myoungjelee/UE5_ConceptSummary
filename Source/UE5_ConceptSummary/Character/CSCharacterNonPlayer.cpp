// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CSCharacterNonPlayer.h"

ACSCharacterNonPlayer::ACSCharacterNonPlayer()
{
}

void ACSCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}
