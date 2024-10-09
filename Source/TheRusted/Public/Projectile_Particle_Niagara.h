// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Particle_Niagara.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AProjectile_Particle_Niagara : public AProjectile_Base
{
	GENERATED_BODY()
public:
	AProjectile_Particle_Niagara();

	UPROPERTY(VisibleAnywhere, Category = Particle)
	class UNiagaraComponent* ParticleComp;		
};
