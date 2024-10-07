// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Healer.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API AProjectile_Healer : public AProjectile_Base
{
	GENERATED_BODY()
	AProjectile_Healer();
protected:
	
	// 무브먼트 컴포넌트
	UPROPERTY(VisibleAnywhere,Category="Movement")
	class UProjectileMovementComponent* PMovementComp;
	// 콜라이더
	UPROPERTY(VisibleAnywhere,Category="Collidor")
	class USphereComponent* SphereCollComp;
	// 메쉬
	UPROPERTY(VisibleAnywhere,Category="Mesh")
	class UStaticMeshComponent* SMeshComp;
	
};
