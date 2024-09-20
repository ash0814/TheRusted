// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KYH_PrimaryProjectile.generated.h"

UCLASS()
class THERUSTED_API AKYH_PrimaryProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKYH_PrimaryProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class USphereComponent* SphereCollisionComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	class UNiagaraComponent* NiagaraComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	class UNiagaraSystem* NiagaraSystem;
	//Projectile Setting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	float ProjectileRange = 1000.f;
};
