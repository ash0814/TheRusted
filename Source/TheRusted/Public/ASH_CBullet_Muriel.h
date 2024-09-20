// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASH_CBullet_Muriel.generated.h"

UCLASS()
class THERUSTED_API AASH_CBullet_Muriel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASH_CBullet_Muriel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* PMovementComp;

	UPROPERTY(VisibleAnywhere, Category = Colider)
	class USphereComponent* SphereCollComp;


	UPROPERTY(VisibleAnywhere, Category = Particle)
	class UParticleSystemComponent* ParticleComp;


private:
	void Die();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
