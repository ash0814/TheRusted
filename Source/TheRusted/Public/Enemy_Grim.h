// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Player_Base.h"
#include "Enemy_Grim.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Grim : public APlayer_Base
{
	GENERATED_BODY()
public:
	AEnemy_Grim();
protected:
	virtual void BeginPlay() override;

public:

};
