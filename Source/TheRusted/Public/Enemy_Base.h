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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	int32 dropItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemyState")
	float currentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyState")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;
};
