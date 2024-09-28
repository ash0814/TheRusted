// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "Player_Muriel.generated.h"


UENUM(BlueprintType)
enum class EMurielUltState : uint8
{
	None UMETA(DisplayName = "None"),
	Ascending UMETA(DisplayName = "Ascending"),
	Descending UMETA(DisplayName = "Descending"),
	Landing UMETA(DisplayName = "Landing")
};

/**
 * 
 */
UCLASS()
class THERUSTED_API APlayer_Muriel : public APlayer_Base
{
	GENERATED_BODY()
public:
	APlayer_Muriel();
protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void LookUp(const FInputActionValue& Value) override;
	virtual void Turn(const FInputActionValue& Value) override;
	virtual void Attack_Primary() override;
	virtual void Attack_Strong() override;
	virtual void Charge_Ultimate() override;
	virtual void Cancle_Ultimate() override;
	virtual void Attack_Ultimate() override;
	virtual void Attack() override;
	UFUNCTION()
	virtual void Landed(const FHitResult& Hit) override;
	FVector GetUltTargetLocation();
	EMurielUltState MurielUltState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FVector UltAttackLocation = FVector::ZeroVector;
	float UltMovementForce = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float UltMaxRange = 6000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* AM_Ult_Land;
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetMurielUltState(EMurielUltState NewMurielUltState);
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void HandleMurielUltState();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	class UParticleSystemComponent* UltPreviewParticleComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	class UParticleSystem* UltPreviewParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class AActor> UltEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AProjectile_Base> magazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<TSubclassOf<class AProjectile_Base>> magazines;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float amount);
	
};
