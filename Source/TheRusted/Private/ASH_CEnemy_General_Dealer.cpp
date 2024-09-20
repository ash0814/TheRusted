// Fill out your copyright notice in the Description page of Project Settings.


#include "ASH_CEnemy_General_Dealer.h"

AASH_CEnemy_General_Dealer::AASH_CEnemy_General_Dealer()
{
}

void AASH_CEnemy_General_Dealer::BeginPlay()
{
	Super::BeginPlay();
	currentAttackTime = 0;
}

void AASH_CEnemy_General_Dealer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//attack every 2 seconds
	/*currentAttackTime += DeltaTime;
	if (currentAttackTime >= 2)
	{
		Attack();
		currentAttackTime = 0;
	}*/
}
