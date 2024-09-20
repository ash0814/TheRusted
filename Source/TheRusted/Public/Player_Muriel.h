// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "Player_Muriel.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API APlayer_Muriel : public APlayer_Base
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	void Attack();
	void StrongAttack();
	void Ultimate();
	
	void SpawnBullet();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class ABullet_Muriel> magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<TSubclassOf<class ABullet_Muriel>> magazines;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float amount);
	
};
