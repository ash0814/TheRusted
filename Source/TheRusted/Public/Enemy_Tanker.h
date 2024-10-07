// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Tanker.generated.h"

class UArrowComponent;
/**
 * 
 */
UCLASS()
class THERUSTED_API AEnemy_Tanker : public AEnemy_Base
{
	GENERATED_BODY()
	
private:
	AEnemy_Tanker();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// arrow component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	class UArrowComponent* FireArrow;

	UFUNCTION(BlueprintCallable)
	void SpawnBullet();
};
