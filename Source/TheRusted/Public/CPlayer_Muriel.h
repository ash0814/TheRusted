// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPlayer.h"
#include "CPlayer_Muriel.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API ACPlayer_Muriel : public ACPlayer
{
	GENERATED_BODY()
	
public:
	void Attack();

	void SpawnBullet();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class ACBullet_Muriel> magazine;

	// apply damage from other actor
	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float amount);

	// apply damage to the hit actor
	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// AnyDamage event
	UFUNCTION(BlueprintCallable)
	void AnyDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
