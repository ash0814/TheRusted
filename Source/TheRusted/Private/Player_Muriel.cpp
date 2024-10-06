
#include "Player_Muriel.h"

#include "GameFramework/Actor.h"
#include "Projectile_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


APlayer_Muriel::APlayer_Muriel()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));

	UltPreviewParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Ult Preview Particle"));
}

void APlayer_Muriel::BeginPlay()
{
	Super::BeginPlay();

	if (magazines.Num())
	{
		magazine = magazines[0];
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Muriel Magazine is Empty"));
	}
	
	SetPlayerMovementState(EPlayerMovementState::Stopped);
	MontagePlay(AM_LevelStart);
}

void APlayer_Muriel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerActionState == EPlayerActionState::Charging_Ultimate)
	{
		if(UltPreviewParticleComp)
		{
			UltPreviewParticleComp->SetWorldLocation(GetUltTargetLocation());
		}
	}
}

void APlayer_Muriel::LookUp(const FInputActionValue& Value)
{
	if(MurielUltState != EMurielUltState::None) return;
	Super::LookUp(Value);
}

void APlayer_Muriel::Turn(const FInputActionValue& Value)
{
	if(MurielUltState != EMurielUltState::None) return;
	Super::Turn(Value);
}

void APlayer_Muriel::Attack_Primary()
{
	magazine = magazines[0];
	MontagePlay(AM_Attack_Primary);
}

void APlayer_Muriel::Attack_Strong()
{
	magazine = magazines[1];
	MontagePlay(AM_Attack_Strong);
}


void APlayer_Muriel::Charge_Ultimate()
{
	MontagePlay(AM_Charge_Ultimate);
	if(UltPreviewParticle)
	{
		UltPreviewParticleComp->SetTemplate(UltPreviewParticle);
		UltPreviewParticleComp->SetWorldLocation(GetUltTargetLocation());
	}
}

void APlayer_Muriel::Cancle_Ultimate()
{
	UltPreviewParticleComp->SetActive(false);
	if(AnimInstance->Montage_IsPlaying(AM_Charge_Ultimate))
	{
		StopAnimMontage(AM_Charge_Ultimate);
	}
}

void APlayer_Muriel::Attack_Ultimate()
{
	SetCombatState(ECombatState::Invincible);
	UltPreviewParticleComp->SetActive(false);
	UltAttackLocation = GetUltTargetLocation();
	UltMovementForce = (UltAttackLocation - GetActorLocation()).Length();
	MontagePlay(AM_Attack_Ultimate);
}

void APlayer_Muriel::Attack()
{
	//FTransform FireTransform = Calc_AttackTransform(FName("Muzzle_01"));
	//DrawDebugLine(GetWorld(), FireTransform.GetLocation(), FireTransform.GetRotation().GetForwardVector() * 2000.f, FColor::Red, true, 5.f, 0, 2.f);
	//DrawDebugDirectionalArrow(GetWorld(), FireTransform.GetLocation(), FireTransform.GetRotation().GetForwardVector() * 200.f, 50.0f, FColor::Red, false, 5.0f);
	
	GetWorld()->SpawnActor<AProjectile_Base>(magazine, FTransform(Calc_AttackTransform(FName("Muzzle_01"))));

}

void APlayer_Muriel::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if(PlayerMovementState != EPlayerMovementState::Stopped)
	{
		PlayerMovementState = EPlayerMovementState::Idle;
	}
	
	if(MurielUltState == EMurielUltState::Descending)
	{
		SetCombatState(ECombatState::None);
		if(AM_Ult_Land)
		{
			PlayAnimMontage(AM_Ult_Land);
		}
		if(UltEffect)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Landed"));
			GetWorld()->SpawnActor<AActor>(UltEffect, Hit.ImpactPoint + GetActorForwardVector() * 300.f, FRotator::ZeroRotator);
		}
	}
}

FVector APlayer_Muriel::GetUltTargetLocation()
{
	// Ultimate 낙하지점 계산
	FVector UltStartLocation = CameraComp->GetComponentLocation();
	FVector UltEndLocation = UltStartLocation + GetActorForwardVector() * UltMaxRange;
	FHitResult UltHit;
	bool bIsVaildRange = GetWorld()->LineTraceSingleByChannel(UltHit, UltStartLocation, UltStartLocation + CameraComp->GetForwardVector() * UltMaxRange, ECC_Visibility);
	if(bIsVaildRange)
	{
		UltEndLocation = UltHit.ImpactPoint;
		//DrawDebugLine(GetWorld(), UltStartLocation, UltEndLocation, FColor::Orange, true, 1.f, 0, 5.f);
	}
	else
	{
		bIsVaildRange = GetWorld()->LineTraceSingleByChannel(UltHit, UltEndLocation, UltEndLocation - FVector::UpVector * UltMaxRange, ECC_Visibility);
		if(bIsVaildRange)
		{
			UltEndLocation = UltHit.ImpactPoint;
		}
	}
	//
	//+
	//DrawDebugLine(GetWorld(), UltEndLocation, FVector(UltEndLocation.X, UltEndLocation.Y, UltEndLocation.Z + 1000.f), FColor::Red, true, 0.2f, 0, 50.f);
	return UltEndLocation;
}

void APlayer_Muriel::SetMurielUltState(EMurielUltState NewMurielUltState)
{
	if(MurielUltState == NewMurielUltState) return;
	
	MurielUltState = NewMurielUltState;
	HandleMurielUltState();
}

void APlayer_Muriel::HandleMurielUltState()
{
	switch (MurielUltState)
	{
	case EMurielUltState::None:
		break;
	case EMurielUltState::Ascending:
		GetCharacterMovement()->Launch(GetActorUpVector() * UltMaxRange * 0.35f + (UltAttackLocation - GetActorLocation()) * 0.3f);
		break;
	case EMurielUltState::Descending:
		GetCharacterMovement()->Launch(-GetActorUpVector() * UltMovementForce * 10.f + (UltAttackLocation - GetActorLocation()) * 1.5f);
		break;
	case EMurielUltState::Landing:
		break;
	}
}

void APlayer_Muriel::ApplyDamage(float amount)
{
	if(PlayerCombatState != ECombatState::Invincible)
	{
		if (BasicStatus.SP > 0)
		{
			BasicStatus.AddSP(-1);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Apply SP Point Once!"));
			return;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
			BasicStatus.AddHP(amount * -1);
		}
	}
}
