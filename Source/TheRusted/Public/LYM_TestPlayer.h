// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LYM_TestPlayer.generated.h"

// Forward Declaration
class UInputMappingContext;
class UInputAction;

UCLASS()
class THERUSTED_API ALYM_TestPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALYM_TestPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void FireCoolTimer(float Duration,float deltaTime);
private:
	bool fireReady;
	float fireTimerTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHP;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxEP;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	int32 MaxSP;
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

	// SpringArmComponent
	UPROPERTY(VisibleAnywhere,Category="Camera")
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere,Category="Camera")
	class UCameraComponent* CameraComp;
	// Player MappingContext
	UPROPERTY(EditAnywhere,Category="Input")
	UInputMappingContext* PlayerMappingContext;
	// Player InputAction
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* MoveIA;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* LookUpIA;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* TurnIA;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* JunpIA;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* AttackIA;
	// Input Function
	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void InputAttack(const FInputActionValue& Value);
	// MoveDirection을 담는 FVector 자료형의 멤버변수
	FVector MoveDirection;
	// pitch 값을 변경해 위아래 움직임을 반대로 움직이게 하는 bool 자료형의 멤버변수
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Control Option")
	bool isInvertLookUp = false;
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<class ALYM_PBullet> magazine;
	UPROPERTY(EditAnywhere,Category="Fire")
	float fireCoolTime;
	UPROPERTY(EditAnywhere,Category="Animation")
	UAnimMontage* AttackAnimMontage;

	void SpawnBullet();
};
