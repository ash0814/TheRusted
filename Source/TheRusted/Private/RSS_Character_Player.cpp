
#include "RSS_Character_Player.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.h"
#include "Components/CapsuleComponent.h"

ARSS_Character_Player::ARSS_Character_Player()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void ARSS_Character_Player::BeginPlay()
{
	Super::BeginPlay();

	if (magazines.Num() > 0) {
		magazine = magazines[0];
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Muriel Magazine is Empty"));
	}
}

void ARSS_Character_Player::Attack_Primary()
{
	MontagePlay(AM_Attack_Primary);
	magazine = magazines[0];
}

void ARSS_Character_Player::Attack_Strong()
{
	MontagePlay(AM_Attack_Strong);
	magazine = magazines[1];
}

void ARSS_Character_Player::Attack_Ultimate()
{
	MontagePlay(AM_Attack_Ultimate);
}

void ARSS_Character_Player::Attack()
{
	FTransform FireTransform = Calc_AttackTransform(FName("WeaponAttachPointR"));
	GetWorld()->SpawnActor<AProjectile_Base>(magazine, FireTransform);

	DrawDebugDirectionalArrow(GetWorld(), FireTransform.GetLocation(), FireTransform.GetLocation() + FireTransform.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
}

void ARSS_Character_Player::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
}