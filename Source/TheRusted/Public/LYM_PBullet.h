// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LYM_PBullet.generated.h"

UCLASS()
class THERUSTED_API ALYM_PBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALYM_PBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere,Category="Movement")
	class UProjectileMovementComponent* PMovementComp;
	UPROPERTY(VisibleAnywhere,Category="Collidor")
	class USphereComponent* SphereCollComp;
	UPROPERTY(VisibleAnywhere, Category = Particle)
	class UParticleSystemComponent* ParticleComp;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComp() const { return PMovementComp; }
};
