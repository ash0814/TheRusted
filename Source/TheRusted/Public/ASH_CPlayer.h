// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ASH_CPlayer.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class THERUSTED_API AASH_CPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AASH_CPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComp;

	// Input

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveIA;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookUpIA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* TurnIA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* JumpIA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* AttackIA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* UltimateIA;


	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void InputAttack(const FInputActionValue& Value);
	void InputUltimate(const FInputActionValue& Value);

	FVector MoveDirection;

	// Attack Animation
	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* StrongAttackAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* HitAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* UltimateAnimMontage;

	bool bCanStrongAttack;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHP;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxEP;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	int32 MaxSP;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxUltimateGauge;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float UltimateGauge;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TArray<int32> QuickSlot;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float currentHP;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float currentEP;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	int32 currentSP;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void StrongAttack();

	virtual void Ultimate();

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
