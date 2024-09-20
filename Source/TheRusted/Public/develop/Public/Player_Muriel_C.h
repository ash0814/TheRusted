// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_C.h"
#include "Player_Muriel_C.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API APlayer_Muriel_C : public APlayer_C
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	void Attack();
	void StrongAttack();
	void Ultimate();
	FTransform Calc_AttackTransform();

	void SpawnBullet();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class ABullet_Muriel_C> magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<TSubclassOf<class ABullet_Muriel_C>> magazines;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float amount);
	
};
