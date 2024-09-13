// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyInterface.h"
#include "GameFramework/Character.h"
#include "CharacterStatus.h"
#include "InputActionValue.h"
#include "CustomPlayerBase.generated.h"

UCLASS()
class THERUSTED_API ACustomPlayerBase : public ACharacter//, public IAnimNotifyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomPlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// public variable
	
	// Input & Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* MoveIA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* JumpIA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* LookHorizontalIA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* LookVerticalIA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* PrimaryIA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* SpecialAttackIA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputAction* UltimateIA;
	
	// Player Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class UCameraComponent* CameraComp;

	//Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimInstance* AnimInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* PrimaryMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* SpecialAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* UltimateMontage;

	// Primary
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Primary)
	TSubclassOf<class AActor> PrimaryPool;
	
protected:
	// protected variable
	
	// Player Status
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	FBasicStatus BasicStatus;
	
	// Muriel Status
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float PrimaryDelay = 0.85f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float EPConsumptionPerSecond = 20.0f;
private:
public:
	
	// Function
	
	// Status
	FBasicStatus GetBasicStatus() const { return BasicStatus; }
	float GetEPConsumptionPerSecond() const { return EPConsumptionPerSecond; }
	void SetEPConsumptionPerSecond(float value) { EPConsumptionPerSecond = value; }
	float GetPrimaryDelay() const { return PrimaryDelay; }
	void SetPrimaryDelay(float value) { PrimaryDelay = value; }
	
	// Input
	void _Move(const FInputActionValue& Value);
	void _Jump(const FInputActionValue& Value);
	void _LookHorizontal(const FInputActionValue& Value);
	void _LookVertical(const FInputActionValue& Value);
	void _Primary(const FInputActionValue& Value);
	void _SpawnPrimary();
	void _SpecialAttack(const FInputActionValue& Value);
	void _Ultimate(const FInputActionValue& Value);
};
