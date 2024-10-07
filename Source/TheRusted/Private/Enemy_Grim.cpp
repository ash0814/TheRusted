// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Grim.h"

#include "Projectile_Base.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemy_Grim::AEnemy_Grim()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(130.0f);
	GetCapsuleComponent()->SetCapsuleRadius(60);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGRIMexe/Characters/Heroes/GRIM/Meshes/GRIM_GDC.GRIM_GDC'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -130.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void AEnemy_Grim::BeginPlay()
{
	Super::BeginPlay();

	if (Projectiles.Num() > 0) {
		SelectedProjectile = Projectiles[0];
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Projectiles is Empty"));
	}

	MontagePlay(AM_LevelStart);
}

void AEnemy_Grim::Attack_Primary()
{
	if (bCanAttack)
	{
		SelectedProjectile = Projectiles[0];
		MontagePlay(AM_Attack_Primary);
	}
}

void AEnemy_Grim::Attack_Strong()
{
	if (bCanAttack)
	{
		SelectedProjectile = Projectiles[1];
		MontagePlay(AM_Attack_Strong);
	}
}

void AEnemy_Grim::Attack_Ultimate()
{
	if (bCanAttack)
	{
		SelectedProjectile = Projectiles[2];
		MontagePlay(AM_Attack_Ultimate);
	}
}

void AEnemy_Grim::Attack()
{
	FTransform FireTransform;
	if(SelectedProjectile == Projectiles[0])
	{
		FireTransform = Calc_AttackTransform(FName("Muzzle_01"));
	}
	else if(SelectedProjectile == Projectiles[1])
	{
		FireTransform = Calc_AttackTransform(FName("FX_Ult_Charge"));
	}
	else if(SelectedProjectile == Projectiles[2])
	{
		FireTransform = Calc_AttackTransform(FName("FX_Ult_Charge"));
	}
	
	DrawDebugDirectionalArrow(GetWorld(), FireTransform.GetLocation(), FireTransform.GetLocation() + FireTransform.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
	
	GetWorld()->SpawnActor<AProjectile_Base>(SelectedProjectile, FireTransform);
}

void AEnemy_Grim::Attacker()
{
	switch(FMath::RandRange(0,2))
	{
		case 0:
			Attack_Primary();
			break;
		
		case 1:
			Attack_Strong();
			break;
		
		case 2:
			Attack_Ultimate();
			break;

		default:
			Attack_Primary();
	}
}

float AEnemy_Grim::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	currentHP -= DamageAmount;

	if(currentHP < 0 )
	{
		Death();
	}
	else
	{
		MontagePlay(AM_Hit);
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemy_Grim::Death()
{
	MontagePlay(AM_Death);
}

void AEnemy_Grim::ExcuteDestroy()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_Explosion, GetActorLocation(), GetActorRotation());
	Destroy();
}
