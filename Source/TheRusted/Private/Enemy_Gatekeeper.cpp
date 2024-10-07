// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Gatekeeper.h"
#include "TheRustedGameModeBase.h"
#include "Projectile_Gatekeeper.h"

AEnemy_Gatekeeper::AEnemy_Gatekeeper()
{
	PrimaryActorTick.bCanEverTick = true;
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Gatekeeper/SCIFI_ROBOT_IK_SK1.SCIFI_ROBOT_IK_SK1'"));
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetRelativeLocationAndRotation(FVector(-2.0f, 5.0f, 0.0f), FRotator(-6.5, -260.0f, -8.0f));
	//(Pitch = -6.500000, Yaw = -260.000000, Roll = -8.000000)
	
	WeaponMesh->SetupAttachment(GetMesh(), FName("rightHandSocket"));
	

	currentHP = 1000.0f;
	MaxHP = 1000.0f;
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Die"));
	// get gamemode
	ATheRustedGameModeBase* _gameMode = Cast<ATheRustedGameModeBase>(GetWorld()->GetAuthGameMode());
	if (_gameMode)
	{
		// add score
		_gameMode->SetCanStoreOpen(true);
	}

	bIsDead = true;
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	OnDieSetState();
}

float AEnemy_Gatekeeper::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ret = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	MontagePlay(AM_HitMontage);
	currentHP -= Damage;
	if (currentHP <= 0)
	{
		Die();
	}
	return ret + Damage;
}

//void AEnemy_Gatekeeper::Attack()
//{
//	//PlayAnimMontage(AM_AttackMontage);
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("GateKeeper Attack"));
//}

void AEnemy_Gatekeeper::SpawnBullet()
{
	FVector FirePosition = WeaponMesh->GetSocketLocation(FName("Muzzle"));
	FRotator FireRotation = GetActorForwardVector().Rotation();
	// spawn projectile
	GetWorld()->SpawnActor<AProjectile_Gatekeeper>(Bullet, FirePosition, FireRotation);
}

