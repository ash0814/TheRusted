// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Shooter.generated.h"

class AProjectile_Base;
/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Shooter : public AEnemy_Base
{
	GENERATED_BODY()
public:
	AEnemy_Shooter();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Attack() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	class USkeletalMeshComponent* MainWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TSubclassOf<class AProjectile_Base> Magazine;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
