// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Healer.h"

#include "Projectile_Healer.h"
#include "Item.h"

AEnemy_Healer::AEnemy_Healer()
{
	// 무기 메쉬 컴포넌트
	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComp->SetupAttachment(GetMesh(), FName("rightHandMiddleSocket"));
	
}

void AEnemy_Healer::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Healer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy_Healer::Healer_Attack()
{
	FVector FirePosition = WeaponMeshComp->GetSocketLocation(FName("Muzzle"));
	FRotator FireRotation = GetActorForwardVector().Rotation();
	DrawDebugDirectionalArrow(GetWorld(), FirePosition, FirePosition + FireRotation.Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
	
	GetWorld()->SpawnActor<AProjectile_Healer>(magazine, FirePosition,FireRotation);
}

void AEnemy_Healer::Die()
{
	bIsDead = true;
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	if (ItemDrop)
	{
		FTransform _transform = GetActorTransform();
		GetWorld()->SpawnActor<AItem>(ItemDrop, _transform);
	}

	OnDieSetState();
}

float AEnemy_Healer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ret = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	MontagePlay(AM_HitMontage);
	currentHP -= Damage;
	if (currentHP <= 0)
	{
		Die();
	}
	return ret + Damage;
}
