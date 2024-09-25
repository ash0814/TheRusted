// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Gatekeeper.h"
#include "TheRustedGameModeBase.h"

AEnemy_Gatekeeper::AEnemy_Gatekeeper()
{
	PrimaryActorTick.bCanEverTick = true;
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/SciFi_Robot/MESHES/SCIFI_ROBOT_IK_SK.SCIFI_ROBOT_IK_SK'"));
	currentHP = 100.0f;
	MaxHP = 100.0f;
}

void AEnemy_Gatekeeper::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Gatekeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy_Gatekeeper::Die()
{
	// get gamemode
	ATheRustedGameModeBase* _gameMode = Cast<ATheRustedGameModeBase>(GetWorld()->GetAuthGameMode());
	if (_gameMode)
	{
		// add score
		_gameMode->SetCanStoreOpen(true);
	}
	Destroy();
}

float AEnemy_Gatekeeper::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	currentHP -= Damage;
	if (currentHP <= 0)
	{
		Die();
	}
	return 0.0f;
}
