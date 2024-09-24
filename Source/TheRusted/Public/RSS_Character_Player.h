// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "RSS_Character_Player.generated.h"

UCLASS()
class THERUSTED_API ARSS_Character_Player : public APlayer_Base
{
	GENERATED_BODY()
public:
	ARSS_Character_Player();
public:
	void BeginPlay() override;
	void Attack_Primary();
	void Attack_Strong();
	void Attack_Ultimate();
	
	void Attack();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AProjectile_Base> magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<TSubclassOf<class AProjectile_Base>> magazines;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float amount);
};
