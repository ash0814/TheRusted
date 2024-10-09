// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile_Particle_Niagara.h"
#include "Projectile_Muriel_StrongAttack.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AProjectile_Muriel_StrongAttack : public AProjectile_Particle_Niagara
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Hit")
	bool bHit;
	
	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* VFX_HitWorld;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* VFX_HitCharacter;
	
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    FVector NormalImpulse, const FHitResult& Hit);
};
