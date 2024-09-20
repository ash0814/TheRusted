// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASH_CPlayer.h"
#include "ASH_CPlayer_Muriel.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AASH_CPlayer_Muriel : public AASH_CPlayer
{
	GENERATED_BODY()
	
public:
	void Attack();
	void StrongAttack();
	void Ultimate();

	void SpawnBullet();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AASH_CBullet_Muriel> magazine;

	// apply damage from other actor
	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float amount);

	// apply damage to the hit actor
	//UFUNCTION(BlueprintCallable)
	//void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// AnyDamage event
	UFUNCTION(BlueprintCallable)
	void AnyDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
