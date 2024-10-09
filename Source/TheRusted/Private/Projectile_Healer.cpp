// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Healer.h"
#include "Player_Muriel.h"
#include "Enemy_base.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShieldComponent.h"
#include "Enemy_Tanker.h"
#include "Enemy_Healer.h"
#include "Kismet/GameplayStatics.h"

AProjectile_Healer::AProjectile_Healer()
{
}

void AProjectile_Healer::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &AProjectile_Healer::OnComponentHit);
}

void AProjectile_Healer::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemy_Base* _Enemy = Cast<AEnemy_Base>(OtherActor);
	if (_Enemy)
	{
		if (Cast<AEnemy_Healer>(_Enemy))
		{
			return;
		}
		_Enemy->currentHP += 100;
		if (_Enemy->currentHP > _Enemy->MaxHP)
		{
			_Enemy->currentHP = _Enemy->MaxHP;
		}
		// play niagara effect here
		PlayNiagaraEffect(_Enemy->GetActorTransform());
	
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
