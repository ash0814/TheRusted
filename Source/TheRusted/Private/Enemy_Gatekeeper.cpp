// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Gatekeeper.h"

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

float AEnemy_Gatekeeper::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	currentHP -= Damage;
	if (currentHP <= 0)
	{
		// get actor that named "SM_Door_01" around this actor


		//AActor* _door = 
			//(FName("SM_Door_Merged_03"));
		Destroy();
	}
	return 0.0f;
}
