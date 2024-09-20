// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "KYH_CharacterStatus.h"
#include "Player_Base.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class THERUSTED_API APlayer_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Base();
	
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
	bool bLookUpInvert = true;

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
	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* StrongAttackAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* HitAnimMontage;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* UltimateAnimMontage;

	bool bCanStrongAttack;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void StrongAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Ultimate();

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	FBasicStatus BasicStatus;

//Util
public:
	FTransform Calc_AttackTransform(FName socketName);
	void MontagePlay(UAnimMontage* animMontage);
	void SetSkeletalMesh(const TCHAR* ObjectToFind);
	
};
