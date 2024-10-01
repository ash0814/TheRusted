// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Healer.h"

AEnemy_Healer::AEnemy_Healer()
{
	// 무기 메쉬 컴포넌트
	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComp->SetupAttachment(GetMesh());
}

void AEnemy_Healer::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Healer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
