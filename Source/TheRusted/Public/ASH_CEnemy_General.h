// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASH_CEnemy.h"
#include "ASH_CEnemy_General.generated.h"

/**
 * 
 */

UCLASS()
class THERUSTED_API AASH_CEnemy_General : public AASH_CEnemy
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AASH_CEnemy_General();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	int32 dropItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AASH_CBullet_Enemy> magazine;


	virtual void Attack();
	virtual void Die();
};