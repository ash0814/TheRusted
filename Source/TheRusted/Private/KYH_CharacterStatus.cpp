// Fill out your copyright notice in the Description page of Project Settings.


#include "KYH_CharacterStatus.h"

KYH_CharacterStatus::KYH_CharacterStatus()
{
}

KYH_CharacterStatus::~KYH_CharacterStatus()
{
}

void FBasicStatus::InitStatus(const FBasicStatus InitStatus)
{
	MaxHP = InitStatus.MaxHP;
	HP = InitStatus.HP;
	MaxEP = InitStatus.MaxEP;
	EP = InitStatus.EP;
	MaxSP = InitStatus.MaxSP;
	SP = InitStatus.SP;
	MaxULTGauge = InitStatus.MaxULTGauge;
	ULTGauge = InitStatus.ULTGauge;
}

void FBasicStatus::AddHP(float Value)
{
	if (HP + Value > MaxHP) HP = MaxHP;
	else if (HP + Value < 0) HP = 0.f;
	else HP += Value;
}

void FBasicStatus::AddEP(float Value)
{
	if (EP + Value > MaxEP) EP = MaxEP;
	else if (EP + Value < 0) EP = 0.f;
	else EP += Value;
}

void FBasicStatus::AddSP(int32 Value)
{
	if (SP + Value > MaxSP) SP = MaxSP;
	else if (SP + Value < 0) SP = 0;
	else SP += Value;
}

void FBasicStatus::AddULTGauge(float Value)
{
	if (ULTGauge + Value > MaxULTGauge) ULTGauge = MaxULTGauge;
	else if (ULTGauge < 0) ULTGauge = 0.f;
	else ULTGauge += Value;
}
