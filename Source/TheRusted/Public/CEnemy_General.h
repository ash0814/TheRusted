// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemy.h"
#include "CEnemy_General.generated.h"

/**
 * 
 */

UCLASS()
class THERUSTED_API ACEnemy_General : public ACEnemy
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ACEnemy_General();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	int32 dropItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class ACBullet_Enemy> magazine;

	virtual void Attack();
	virtual void Die();
};
