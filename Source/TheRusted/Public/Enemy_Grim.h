// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Grim.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Grim : public AEnemy_Base
{
	GENERATED_BODY()
public:
	AEnemy_Grim();
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_LevelStart;
	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_Attack_Primary;
	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_Attack_Strong;
	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_Attack_Ultimate;
	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_Hit;
	
	void Attack_Primary();
	void Attack_Strong();
	void Attack_Ultimate();	
	virtual void Attack() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AProjectile_Base> SelectedProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TArray<TSubclassOf<class AProjectile_Base>> Projectiles;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
