// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStatus.generated.h"
/**
 *
 */
class THERUSTED_API CharacterStatus
{
public:
	CharacterStatus();
	~CharacterStatus();
};

USTRUCT(Atomic, BlueprintType)
struct FBasicStatus
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxEP = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EP = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxSP = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxULTGauge = 1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ULTGauge = 0.f;
public:
	void InitStatus(const FBasicStatus InitStatus);
	void AddHP(float Value);
	void AddEP(float Value);
	void AddSP(int32 Value);
	void AddULTGauge(float Value);
};