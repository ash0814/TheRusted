// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "Player_Muriel.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API APlayer_Muriel : public APlayer_Base
{
	GENERATED_BODY()
public:
	APlayer_Muriel();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack_Primary() override;
	virtual void Attack_Strong() override;
	virtual void Attack_Ultimate() override;	
	virtual void Attack() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AProjectile_Base> magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<TSubclassOf<class AProjectile_Base>> magazines;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float amount);
	
};
