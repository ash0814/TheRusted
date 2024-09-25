// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Particle_Niagara.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

AProjectile_Particle_Niagara::AProjectile_Particle_Niagara()
{
	ParticleComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(SphereComp);
	ParticleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleComp->bAutoActivate = true;
}
