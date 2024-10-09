// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Gatekeeper.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AProjectile_Gatekeeper : public AProjectile_Base
{
	GENERATED_BODY()
	
public:
	AProjectile_Gatekeeper();

protected:
	virtual void BeginPlay() override;
	
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
