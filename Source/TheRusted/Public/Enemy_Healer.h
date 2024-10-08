// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Healer.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Healer : public AEnemy_Base
{
	GENERATED_BODY()
	AEnemy_Healer();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category="EquitItem")
	class UStaticMeshComponent* WeaponMeshComp;
public:
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void Healer_Attack();
	
	UPROPERTY(EditAnywhere,Category="Animation")
	UAnimMontage* AttackAnimMontage;
	UPROPERTY(EditAnywhere,Category = "Fire")
	TSubclassOf<class AProjectile_Healer> magazine;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDieSetState();

	void Die();

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsDead = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* AM_HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class AItem> ItemDrop;
};
