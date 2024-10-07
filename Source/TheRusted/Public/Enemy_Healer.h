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
	virtual void Attack() override;
	
	UPROPERTY(EditAnywhere,Category="Animation")
	UAnimMontage* AttackAnimMontage;
	UPROPERTY(EditAnywhere,Category = "Fire")
	TSubclassOf<class AProjectile_Healer> magazine;
	
};
