// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Tanker.generated.h"

class UArrowComponent;
/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Tanker : public AEnemy_Base
{
	GENERATED_BODY()
	
private:
	AEnemy_Tanker();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDieSetState();

	void Die();

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// arrow component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	class UArrowComponent* FireArrow;

	UFUNCTION(BlueprintCallable)
	void SpawnBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* AM_HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class AItem> ItemDrop;
};
