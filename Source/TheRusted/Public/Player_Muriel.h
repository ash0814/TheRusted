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
	void UltimateAction(float DeltaTime);

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void Attack_Primary() override;
	virtual void Attack_Strong() override;
	virtual void Charge_Ultimate() override;
	virtual void Cancle_Ultimate() override;
	virtual void Attack_Ultimate() override;
	virtual void Attack() override;
	FVector GetUltTargetLocation();
	FVector UltFirstLocation;
	FVector UltFallingLocation;
	float UltTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FVector UltAttackLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float UltMaxRange = 4000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AProjectile_Base> magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<TSubclassOf<class AProjectile_Base>> magazines;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float amount);
	

};
