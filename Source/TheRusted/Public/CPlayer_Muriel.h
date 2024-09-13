// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPlayer.h"
#include "CPlayer_Muriel.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API ACPlayer_Muriel : public ACPlayer
{
	GENERATED_BODY()
	
public:
	void Attack();

	void SpawnBullet();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class ACBullet_Muriel> magazine;


};
