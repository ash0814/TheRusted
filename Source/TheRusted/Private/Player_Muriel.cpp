
#include "Player_Muriel.h"
#include "GameFramework/Actor.h"
#include "Bullet_Muriel.h"

void APlayer_Muriel::BeginPlay()
{
	Super::BeginPlay();
	if (magazines.Num() > 0) {
		magazine = magazines[0];
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Muriel Magazine is Empty"));
	}
}

void APlayer_Muriel::Attack()
{
	MontagePlay(AttackAnimMontage);
	magazine = magazines[0];
}

void APlayer_Muriel::StrongAttack()
{
	MontagePlay(StrongAttackAnimMontage);
	magazine = magazines[1];
}

void APlayer_Muriel::Ultimate()
{
	MontagePlay(UltimateAnimMontage);
}

void APlayer_Muriel::SpawnBullet()
{
	FTransform _firePosition = Calc_AttackTransform(FName("WeaponAttachPointR"));
	GetWorld()->SpawnActor<ABullet_Muriel>(magazine, _firePosition);

	DrawDebugDirectionalArrow(GetWorld(), _firePosition.GetLocation(), _firePosition.GetLocation() + _firePosition.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
}

void APlayer_Muriel::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
}