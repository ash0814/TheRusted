// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet_Muriel.generated.h"

UCLASS()
class THERUSTED_API ACBullet_Muriel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBullet_Muriel();

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

    UFUNCTION(BlueprintCallable)
	// apply damage to the hit actor
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	void Die();
};
