// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Shooter.h"

#include "Projectile_Base.h"

AEnemy_Shooter::AEnemy_Shooter()
{
	MainWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Main Weapon"));
	//MainWeapon->SetRelativeLocationAndRotation(FVector(-2.0f, 2.0f, -3.0f), FRotator(11.0f, -130.0f, 3.0f));
	MainWeapon->SetupAttachment(GetMesh(), FName("Weapon"));
}

void AEnemy_Shooter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Shooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy_Shooter::Attack()
{
	Super::Attack();
	GetWorld()->SpawnActor<AProjectile_Base>(Magazine, 	MainWeapon->GetSocketTransform(FName("muzzle")));
}
