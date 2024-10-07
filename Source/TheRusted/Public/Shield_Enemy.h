// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield_Enemy.generated.h"

UCLASS()
class THERUSTED_API AShield_Enemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	class USphereComponent* ShieldSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	class UNiagaraComponent* ShieldEffect;

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void DestroyShield();
};
