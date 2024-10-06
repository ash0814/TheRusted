// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Gatekeeper.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Gatekeeper : public AEnemy_Base
{
	GENERATED_BODY()
	
private:
	AEnemy_Gatekeeper();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDieSetState();

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Attack();

	void SpawnBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* AM_AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* AM_HitMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* AM_DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDead = false;
};
