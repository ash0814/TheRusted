// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Healer.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AProjectile_Healer : public AProjectile_Base
{
	GENERATED_BODY()
private:
	AProjectile_Healer();

protected:
	virtual void BeginPlay() override;
	
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayNiagaraEffect(FTransform hitTransform);
};
