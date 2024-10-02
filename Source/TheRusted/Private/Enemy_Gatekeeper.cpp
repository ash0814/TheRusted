// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Gatekeeper.h"
#include "TheRustedGameModeBase.h"

AEnemy_Gatekeeper::AEnemy_Gatekeeper()
{
	PrimaryActorTick.bCanEverTick = true;
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Gatekeeper/SCIFI_ROBOT_IK_SK1.SCIFI_ROBOT_IK_SK1'"));
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetRelativeLocationAndRotation(FVector(-2.0f, 5.0f, 0.0f), FRotator(10.0f, -130.0f, 0.0f));
	WeaponMesh->SetupAttachment(GetMesh(), FName("rightHandMiddleSocket"));
	

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GateKeeper Attack"));
	
	// get weapon mesh socket name 'muzzle'
	FVector FirePosition = WeaponMesh->GetSocketLocation(FName("Muzzle"));
	FRotator FireRotation = GetActorForwardVector().Rotation();
}
