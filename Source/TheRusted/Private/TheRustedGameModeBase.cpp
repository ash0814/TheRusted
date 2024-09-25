// Fill out your copyright notice in the Description page of Project Settings.


#include "TheRustedGameModeBase.h"

void ATheRustedGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATheRustedGameModeBase::SetCanStoreOpen(bool bCanOpen)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SetCanStoreOpen"));
	bCanStoreOpen = bCanOpen;
}
