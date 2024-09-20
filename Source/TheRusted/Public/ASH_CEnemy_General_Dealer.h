// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASH_CEnemy_General.h"
#include "ASH_CEnemy_General_Dealer.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AASH_CEnemy_General_Dealer : public AASH_CEnemy_General
{
	GENERATED_BODY()
	
public:
	AASH_CEnemy_General_Dealer();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float currentAttackTime;
};
