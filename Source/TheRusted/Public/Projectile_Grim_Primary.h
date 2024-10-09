// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile_Particle_Cascade.h"
#include "Projectile_Grim_Primary.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AProjectile_Grim_Primary : public AProjectile_Particle_Cascade
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* VFX_Spawn;
	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* VFX_NoHit;
	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* VFX_HitWorld;
	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* VFX_HitWater;
	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* VFX_HitCharacter;

	UPROPERTY(EditAnywhere, Category = "Hit")
	bool bHit = false;

	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
