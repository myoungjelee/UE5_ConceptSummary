// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/CSStageGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Physics/CSCollision.h"
#include "Character/CSCharacterNonPlayer.h"
#include "Item/CSItemBox.h"

// Sets default values
ACSStageGimmick::ACSStageGimmick()
{
	// Stage Section
	Stage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stage"));
	SetRootComponent(Stage);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Stages/SM_SQUARE.SM_SQUARE'"));
	if (StageMeshRef.Object)
	{
		Stage->SetStaticMesh(StageMeshRef.Object);
	}

	StageTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("StageTrigger"));
	StageTrigger->SetupAttachment(Stage);
	StageTrigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	StageTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	StageTrigger->SetCollisionProfileName(CPROFILE_CSTRIGGER);
	StageTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACSStageGimmick::OnStageTriggerBeginOverlap);

	// Gate Section
	static FName GateSockets[] = { TEXT("EGate"), TEXT("WGate"), TEXT("SGate"), TEXT("NGate") };
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_GATE.SM_GATE'"));
	for (FName GateSocket : GateSockets)
	{
		UStaticMeshComponent* Gate = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);
		Gate->SetStaticMesh(GateMeshRef.Object);
		Gate->SetupAttachment(Stage, GateSocket);
		Gate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		Gate->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		Gates.Add(GateSocket, Gate);

		FName TriggerName = *GateSocket.ToString().Append(TEXT("Trigger"));
		UBoxComponent* GateTrigger = CreateDefaultSubobject<UBoxComponent>(TriggerName);
		GateTrigger->SetupAttachment(Stage, GateSocket);
		GateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		GateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		GateTrigger->SetCollisionProfileName(CPROFILE_CSTRIGGER);
		GateTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACSStageGimmick::OnGateTriggerBeginOverlap);
		GateTrigger->ComponentTags.Add(GateSocket);

		GateTriggers.Add(GateTrigger);
	}

	// State Section
	CurrentState = EStageState::READY;
	StateChangeActions.Add(EStageState::READY, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &ACSStageGimmick::SetReady)));
	StateChangeActions.Add(EStageState::FIGHT, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &ACSStageGimmick::SetFight)));
	StateChangeActions.Add(EStageState::REWARD, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &ACSStageGimmick::SetChooseReward)));
	StateChangeActions.Add(EStageState::NEXT, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &ACSStageGimmick::SetChooseNext)));

	// Fight Section
	EnemySpawnTime = 2.0f;
	EnemyClass = ACSCharacterNonPlayer::StaticClass();

	// Reward Section
	RewardBoxClass = ACSItemBox::StaticClass();
	for (FName GateSocket : GateSockets)
	{
		FVector BoxLoc = Stage->GetSocketLocation(GateSocket) / 2;
		RewardBoxLocs.Add(GateSocket, BoxLoc);
	}
}

void ACSStageGimmick::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(CurrentState);
}

void ACSStageGimmick::OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	SetState(EStageState::FIGHT);
}

void ACSStageGimmick::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	check(OverlappedComponent->ComponentTags.Num() == 1);
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(1));
	check(Stage->DoesSocketExist(SocketName));

	FVector NewLoc = Stage->GetSocketLocation(SocketName);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Param(SCENE_QUERY_STAT(GateTrigger), false, this);
	bool bResult = GetWorld()->OverlapMultiByObjectType(OverlapResults, NewLoc, FQuat::Identity, FCollisionObjectQueryParams::InitType::AllStaticObjects, FCollisionShape::MakeSphere(775.0f), Param);

	if (!bResult)
	{
		GetWorld()->SpawnActor<ACSStageGimmick>(NewLoc, FRotator::ZeroRotator);
	}
}

void ACSStageGimmick::OpenAllGates()
{
	for (auto Gate : Gates)
	{
		(Gate.Value)->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void ACSStageGimmick::CloseAllGates()
{
	for (auto Gate : Gates)
	{
		(Gate.Value)->SetRelativeRotation(FRotator::ZeroRotator);
	}
}

void ACSStageGimmick::SetState(EStageState InNewState)
{
	CurrentState = InNewState;

	if (StateChangeActions.Contains(InNewState))
	{
		StateChangeActions[CurrentState].StageDelegate.ExecuteIfBound();
	}
}

void ACSStageGimmick::SetReady()
{
	StageTrigger->SetCollisionProfileName(CPROFILE_CSTRIGGER);
	for (auto GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	OpenAllGates();
}

void ACSStageGimmick::SetFight()
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	CloseAllGates();

	GetWorld()->GetTimerManager().SetTimer(EnemyTimerHandle, this, &ACSStageGimmick::OnEnemySpawn, EnemySpawnTime, false);
}

void ACSStageGimmick::SetChooseReward()
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	CloseAllGates();
	SpawnRewardBoxes();
}

void ACSStageGimmick::SetChooseNext()
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(CPROFILE_CSTRIGGER);
	}

	OpenAllGates();
}

void ACSStageGimmick::OnEnemyDestroyed(AActor* DestroyedActor)
{
	SetState(EStageState::REWARD);
}

void ACSStageGimmick::OnEnemySpawn()
{
	const FVector SpawnLoc = GetActorLocation() + FVector::UpVector * 88.0f;
	ACSCharacterNonPlayer* CSEnemy = GetWorld()->SpawnActor<ACSCharacterNonPlayer>(EnemyClass, SpawnLoc, FRotator::ZeroRotator);
	if (CSEnemy)
	{
		CSEnemy->OnDestroyed.AddDynamic(this, &ACSStageGimmick::OnEnemyDestroyed);
	}
}

void ACSStageGimmick::OnRewardTrggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())
		{
			ACSItemBox* ValidItemBox = RewardBox.Get();
			AActor* OverlappedBox = OverlappedComponent->GetOwner();
			if (OverlappedBox != ValidItemBox)
			{
				ValidItemBox->Destroy();
			}
		}
	}

	SetState(EStageState::NEXT);
}

void ACSStageGimmick::SpawnRewardBoxes()
{
	for (const auto& RewardBoxLoc : RewardBoxLocs)
	{
		FVector WorldSpawnLoc = GetActorLocation() + RewardBoxLoc.Value + FVector(0.0f, 0.0f, 30.0f);
		ACSItemBox* RewardBoxActor = GetWorld()->SpawnActor<ACSItemBox>(RewardBoxClass, WorldSpawnLoc, FRotator::ZeroRotator);
		if (RewardBoxActor)
		{
			RewardBoxActor->Tags.Add(RewardBoxLoc.Key);
			RewardBoxActor->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ACSStageGimmick::OnRewardTrggerBeginOverlap);
			RewardBoxes.Add(RewardBoxActor);
		}
	}
}



