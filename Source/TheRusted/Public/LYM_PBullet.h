// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LYM_PBullet.generated.h"

UCLASS()
class THERUSTED_API ALYM_PBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALYM_PBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere,Category="Movement")
	class UProjectileMovementComponent* PMovementComp;
	UPROPERTY(VisibleAnywhere,Category="Collidor")
	class USphereComponent* SphereCollComp;
	UPROPERTY(VisibleAnywhere,Category="Mesh")
	class UStaticMeshComponent* SMeshComp;
};
