// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Player_Base.h"
#include "Enemy_Grim.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Grim : public APlayer_Base
{
	GENERATED_BODY()
public:
	AEnemy_Grim();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack_Primary() override;
	virtual void Attack_Strong() override;
	virtual void Attack_Ultimate() override;	
	virtual void Attack() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AProjectile_Base> SelectedProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TArray<TSubclassOf<class AProjectile_Base>> Projectiles;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
