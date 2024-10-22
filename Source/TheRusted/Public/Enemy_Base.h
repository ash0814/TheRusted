// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Base.h"
#include "CharacterStatus.h"
#include "Enemy_Base.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Base : public ACharacter_Base
{
	GENERATED_BODY()
protected:
	AEnemy_Base();
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Movement")
	bool bCanMove = true;
	UPROPERTY(EditAnywhere, Blueprintable, Category = "Movement")
	bool bCanAttack = true;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Movement")
	bool isDead = false;

	virtual void Attack();

	virtual void Death();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	int32 dropItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyState")
	float currentHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyState")
	float MaxHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyState")
	float MaxEP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyState")
	float currentEP = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyState")
	float MaxULTGauge = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyState")
	float ULTGauge = 0.f;
	
	FTransform Calc_AttackTransform(FName socketName, float AttackRange = 10000.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AProjectile_Base> Bullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldComponent")
	class UShieldComponent* ShieldComponent;

	UFUNCTION(BlueprintCallable)
	void SetShield();
};
