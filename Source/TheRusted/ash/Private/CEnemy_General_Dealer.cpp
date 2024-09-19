// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/CEnemy_General_Dealer.h"

ACEnemy_General_Dealer::ACEnemy_General_Dealer()
{
}

void ACEnemy_General_Dealer::BeginPlay()
{
	Super::BeginPlay();
	currentAttackTime = 0;
}

void ACEnemy_General_Dealer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//attack every 2 seconds
	currentAttackTime += DeltaTime;
	if (currentAttackTime >= 2)
	{
		Attack();
		currentAttackTime = 0;
	}
}
