// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CSCharacterNonPlayer.h"
#include "Engine/AssetManager.h"
#include "Ai/CSAIController.h"
#include "CharacterStat/CSCharacterStatComponent.h"

ACSCharacterNonPlayer::ACSCharacterNonPlayer()
{
	GetMesh()->SetHiddenInGame(true);

	AIControllerClass = ACSAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ACSCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ensure(NPCMeshes.Num() > 0);
	int32 RandIndex = FMath::RandRange(0, NPCMeshes.Num() - 1);
	NPCMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(NPCMeshes[RandIndex], FStreamableDelegate::CreateUObject(this, &ACSCharacterNonPlayer::NPCMeshLoadCompleted));
}

void ACSCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	ACSAIController* CSAIController = Cast<ACSAIController>(GetController());
	if (CSAIController)
	{
		CSAIController->StopAI();
	}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}

void ACSCharacterNonPlayer::NPCMeshLoadCompleted()
{
	if (NPCMeshHandle.IsValid())
	{
		USkeletalMesh* NPCMesh = Cast<USkeletalMesh>(NPCMeshHandle->GetLoadedAsset());
		if (NPCMesh)
		{
			GetMesh()->SetSkeletalMesh(NPCMesh);
			GetMesh()->SetHiddenInGame(false);
		}
	}

	NPCMeshHandle->ReleaseHandle();
}

float ACSCharacterNonPlayer::GetAIPatrolRadius()
{
	return 800.0f;
}

float ACSCharacterNonPlayer::GetAIDetectRange()
{
	return 400.0f;
}

float ACSCharacterNonPlayer::GetAIAttackRange()
{
	return Stat->GetTotalStat().AttackRange + Stat->GetAttackRadius() * 2;
}

float ACSCharacterNonPlayer::GetAITurnSpeed()
{
	return 2.0f;
}

void ACSCharacterNonPlayer::AttackByAI()
{
	ProcessComboCommand();
}

void ACSCharacterNonPlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ACSCharacterNonPlayer::NotifyComboActionEnd()
{
	Super::NotifyComboActionEnd();

	OnAttackFinished.ExecuteIfBound();
}
