
#include "Player_Muriel.h"

#include "GameFramework/Actor.h"
#include "Projectile_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"


APlayer_Muriel::APlayer_Muriel()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void APlayer_Muriel::BeginPlay()
{
	Super::BeginPlay();

	if (magazines.Num() > 0) {
		magazine = magazines[0];
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Muriel Magazine is Empty"));
	}

	SetPlayerMovementState(EPlayerMovementState::Stopped);
	MontagePlay(AM_LevelStart);
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

	// Ultimate 낙하지점 계산
	FVector UltStartLocation = CameraComp->GetComponentLocation();
	FVector UltEndLocation;
	FHitResult UltHit;
	bool bIsVaildRange = GetWorld()->LineTraceSingleByChannel(UltHit, UltStartLocation, UltStartLocation + CameraComp->GetForwardVector() * UltMaxRange, ECC_Visibility);
	if(bIsVaildRange)
	{
		UltEndLocation = UltHit.ImpactPoint;
		DrawDebugLine(GetWorld(), UltStartLocation, UltEndLocation, FColor::Orange, true, 1.f, 0, 5.f);
	}
	else
	{
		UltEndLocation = UltStartLocation + GetActorForwardVector() * UltMaxRange;
	}
	DrawDebugLine(GetWorld(), UltEndLocation, FVector(UltEndLocation.X, UltEndLocation.Y, UltEndLocation.Z + 1000.f), FColor::Red, true, 0.2f, 0, 50.f);
}

void APlayer_Muriel::Cancle_Ultimate()
{
	if(AnimInstance->Montage_IsPlaying(AM_Charge_Ultimate))
	{
		StopAnimMontage(AM_Charge_Ultimate);
	}
}

void APlayer_Muriel::Attack_Ultimate()
{
	MontagePlay(AM_Attack_Ultimate);
}

void APlayer_Muriel::Attack()
{
	FTransform FireTransform = Calc_AttackTransform(FName("Muzzle_01"));
	//DrawDebugLine(GetWorld(), FireTransform.GetLocation(), FireTransform.GetRotation().GetForwardVector() * 2000.f, FColor::Red, true, 5.f, 0, 2.f);
	//DrawDebugDirectionalArrow(GetWorld(), FireTransform.GetLocation(), FireTransform.GetRotation().GetForwardVector() * 200.f, 50.0f, FColor::Red, false, 5.0f);
	
	GetWorld()->SpawnActor<AProjectile_Base>(magazine, FireTransform);

}


void APlayer_Muriel::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
}