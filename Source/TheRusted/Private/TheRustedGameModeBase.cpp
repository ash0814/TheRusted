// Fill out your copyright notice in the Description page of Project Settings.


#include "TheRustedGameModeBase.h"
#include "Player_Muriel.h"

void ATheRustedGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATheRustedGameModeBase::SetCanStoreOpen(bool bCanOpen)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SetCanStoreOpen"));
	bCanStoreOpen = bCanOpen;
}

void ATheRustedGameModeBase::AddPlayerUltimateGauge(float value)
{
	// get player character
	auto PlayerCharacter = Cast<APlayer_Muriel>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (PlayerCharacter)
	{
		PlayerCharacter->ChargeUltimateGauge(value);
	}
}
