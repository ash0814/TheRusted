// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Healer.h"

#include "Projectile_Healer.h"

AEnemy_Healer::AEnemy_Healer()
{
	// 무기 메쉬 컴포넌트
	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComp->SetupAttachment(GetMesh(), FName(TEXT("AK47")));
	
}

void AEnemy_Healer::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Healer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy_Healer::Attack()
{
	FTransform Transform;
	DrawDebugDirectionalArrow(GetWorld(), Transform.GetLocation(), Transform.GetLocation() + Transform.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
	
	GetWorld()->SpawnActor<AProjectile_Healer>(magazine, Transform);
}
