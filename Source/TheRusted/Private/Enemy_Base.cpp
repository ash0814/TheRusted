// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Base.h"

AEnemy_Base::AEnemy_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), FName("rightHandSocket"));
}

void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemy_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
