// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Tanker.h"
#include "Player_Muriel.h"
#include "Enemy_base.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShieldComponent.h"
#include "Enemy_Tanker.h"
#include "Kismet/GameplayStatics.h"

AProjectile_Tanker::AProjectile_Tanker()
{
}

void AProjectile_Tanker::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &AProjectile_Tanker::OnComponentHit);
}

void AProjectile_Tanker::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemy_Base* _Enemy = Cast<AEnemy_Base>(OtherActor);
	if (_Enemy)
	{
		if (Cast<AEnemy_Tanker>(_Enemy))
		{
			return;
		}
		auto &_shield = _Enemy->ShieldComponent;
		if (_shield)
		{
			_shield->SpawnShield();
		}
	} else {
		APlayer_Muriel* _player = Cast<APlayer_Muriel>(OtherActor);
		if (_player)
		{
			UGameplayStatics::ApplyDamage(_player, 5, nullptr, this, nullptr);
			/*_player->ApplyDamage(10);*/
		}
	}
	Destroy();
}
