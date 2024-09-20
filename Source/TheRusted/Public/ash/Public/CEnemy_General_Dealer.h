// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemy_General.h"
#include "CEnemy_General_Dealer.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API ACEnemy_General_Dealer : public ACEnemy_General
{
	GENERATED_BODY()
	
public:
	ACEnemy_General_Dealer();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float currentAttackTime;
};
