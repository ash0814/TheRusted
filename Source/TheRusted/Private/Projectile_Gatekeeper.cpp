// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Gatekeeper.h"
#include "Player_Muriel.h"

AProjectile_Gatekeeper::AProjectile_Gatekeeper()
{

}

void AProjectile_Gatekeeper::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile_Gatekeeper::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		APlayer_Muriel* _player = Cast<APlayer_Muriel>(OtherActor);
		if (_player)
		{
			_player->ApplyDamage(100);
		}
	}
}
