// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Particle_Cascade.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile_Particle_Cascade::AProjectile_Particle_Cascade()
{
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(SphereComp);
	ParticleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleComp->bAutoActivate = true;
	ParticleComp->bAutoDestroy = true;
}
