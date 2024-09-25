// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Base.h"
#include "InputActionValue.h"
#include "KYH_CharacterStatus.h"
#include "Player_Base.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class THERUSTED_API APlayer_Base : public ACharacter_Base
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

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComp;

	// Input
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Move;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* IA_LookUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bLookUpInvert = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* IA_Turn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* IA_Attack_Primary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* IA_Attack_Strong;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* IA_Attack_Ultimate;

	bool bCanMove = true;
	bool bCanAttack = true;

	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void Input_Attack_Primary(const FInputActionValue& Value);
	void Input_Attack_Strong(const FInputActionValue& Value);
	void Input_Attack_Ultimate(const FInputActionValue& Value);

	FVector MoveDirection;

	// Animation
	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_LevelStart;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_Attack_Primary;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_Attack_Strong;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_Attack_Ultimate;

	UPROPERTY(EditAnywhere, Category = Animation)
	class UAnimMontage* AM_Hit;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack_Primary();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack_Strong();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack_Ultimate();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	FBasicStatus BasicStatus;

	FTransform Calc_AttackTransform(FName socketName, float AttackRange = 20000);

};
