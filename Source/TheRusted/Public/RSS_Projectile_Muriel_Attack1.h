// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSS_Projectile_Muriel_Attack1.generated.h"

UCLASS()
class THERUSTED_API ARSS_Projectile_Muriel_Attack1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARSS_Projectile_Muriel_Attack1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(visibleAnywhere, category = Collider)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* VFX_Projectile;

	// UPROPERTY(EditAnywhere)
	// class USoundBase* SFX_Fire;
	
	UPROPERTY(EditAnywhere)
	class UParticleSystem* VFX_NoHit;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* VFX_Hit_Character;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* VFX_Hit_Wolrd;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* VFX_Hit_Water;
	
	UFUNCTION()
	void DestroyProjectile();
};
