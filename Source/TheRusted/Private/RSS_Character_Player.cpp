
#include "RSS_Character_Player.h"
#include "GameFramework/Actor.h"
#include "Bullet_Muriel.h"
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

void ARSS_Character_Player::Attack()
{
	MontagePlay(AttackAnimMontage);
	magazine = magazines[0];
}

void ARSS_Character_Player::StrongAttack()
{
	MontagePlay(StrongAttackAnimMontage);
	magazine = magazines[1];
}

void ARSS_Character_Player::Ultimate()
{
	MontagePlay(UltimateAnimMontage);
}

void ARSS_Character_Player::SpawnBullet()
{
	FTransform _firePosition = Calc_AttackTransform(FName("WeaponAttachPointR"));
	GetWorld()->SpawnActor<ABullet_Muriel>(magazine, _firePosition);

	DrawDebugDirectionalArrow(GetWorld(), _firePosition.GetLocation(), _firePosition.GetLocation() + _firePosition.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
}

void ARSS_Character_Player::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
}