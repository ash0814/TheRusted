
#include "Player_Muriel.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

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

	MontagePlay(AM_LevelStart);
}

void APlayer_Muriel::Attack_Primary()
{
	if (bCanAttack) {
		//bCanAttack = false;
		magazine = magazines[0];
		MontagePlay(AM_Attack_Primary);
	}
}

void APlayer_Muriel::Attack_Strong()
{
	if (bCanAttack) {
		bCanAttack = false;
		bCanMove = false;
		magazine = magazines[1];
		MontagePlay(AM_Attack_Strong);
	}
}

void APlayer_Muriel::Attack_Ultimate()
{
	//MontagePlay(AM_Attack_Ultimate);
	if (bCanAttack) {
		bCanAttack = false;
		bCanMove = false;
		MontagePlay(AM_Attack_Ultimate);
	}
}

void APlayer_Muriel::Attack()
{
	FTransform FireTransform = Calc_AttackTransform(FName("WeaponAttachPointR"));
	DrawDebugDirectionalArrow(GetWorld(), FireTransform.GetLocation(), FireTransform.GetLocation() + FireTransform.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
	
	GetWorld()->SpawnActor<AProjectile_Base>(magazine, FireTransform);

}


void APlayer_Muriel::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
}