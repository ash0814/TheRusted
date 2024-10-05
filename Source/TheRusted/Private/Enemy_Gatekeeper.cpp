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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Die"));
	// get gamemode
	ATheRustedGameModeBase* _gameMode = Cast<ATheRustedGameModeBase>(GetWorld()->GetAuthGameMode());
	if (_gameMode)
	{
		// add score
		_gameMode->SetCanStoreOpen(true);
	}
	// get anim instance
	//UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	//// check if anim montage is playing
	//if (_animInstance->Montage_IsPlaying(AM_DeathMontage))
	//{
	//	// stop montage
	//	_animInstance->Montage_Stop(0.0f, AM_DeathMontage);
	//}
	//Destroy();
	bIsDead = true;
	SetActorEnableCollision(false);
	//SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	OnDieSetState();
}

float AEnemy_Gatekeeper::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	MontagePlay(AM_HitMontage);
	currentHP -= Damage;
	if (currentHP <= 0)
	{
		Die();
		//MontagePlay(AM_DeathMontage);
	}
	return 0.0f;
}

void AEnemy_Gatekeeper::Attack()
{
	// play montage
	MontagePlay(AM_AttackMontage);
	// wait until montage is finished

}

void AEnemy_Gatekeeper::SpawnBullet()
{
	FVector FirePosition = WeaponMesh->GetSocketLocation(FName("Muzzle"));
	FRotator FireRotation = GetActorForwardVector().Rotation();
	// spawn projectile
	GetWorld()->SpawnActor<AProjectile_Gatekeeper>(AProjectile_Gatekeeper::StaticClass(), FirePosition, FireRotation);
}

