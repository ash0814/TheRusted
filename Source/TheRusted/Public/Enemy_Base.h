// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Base.h"
#include "Enemy_Base.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Base : public ACharacter_Base
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	int32 dropItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AASH_CBullet_Enemy> magazine;

	
	
};
