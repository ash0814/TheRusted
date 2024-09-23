// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Particle_Cascade.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AProjectile_Particle_Cascade : public AProjectile_Base
{
	GENERATED_BODY()
public:
	AProjectile_Particle_Cascade();
	
	UPROPERTY(VisibleAnywhere, Category = Particle)
	class UParticleSystemComponent* ParticleComp;
};
