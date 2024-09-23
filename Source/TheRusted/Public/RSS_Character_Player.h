// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "RSS_Character_Player.generated.h"

UCLASS()
class THERUSTED_API ARSS_Character_Player : public APlayer_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARSS_Character_Player();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//INPUT
public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Player;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Turn;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LookUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement )
	bool bIsInvertLookUp = true;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Attack1;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Attack2;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Skill1;

	void Input_Turn(const struct FInputActionValue& inputValue);
	void Input_LookUp(const struct FInputActionValue& inputValue);
	void Input_Move(const struct FInputActionValue& inputValue);
	void Input_Jump(const struct FInputActionValue& inputValue);
	void Input_Attack1(const struct FInputActionValue& inputValue);
	void Input_Attack2(const struct FInputActionValue& inputValue);
	void Input_Skill1(const struct FInputActionValue& inputValue);

//AnimMantage
public:
	UAnimInstance* AnimInstance;
	
	UPROPERTY(EditAnywhere, Category = Animation)
	UAnimMontage* AM_Attack1;
	
	UPROPERTY(EditAnywhere, Category = Animation)
	UAnimMontage* AM_Attack2;

	UPROPERTY(EditAnywhere, Category = Animation)
	UAnimMontage* AM_Skill1;

	
	void MontagePlay(UAnimMontage* animMontage);

//Move
private:
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector MoveDirection;

//CAMERA
public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* CameraComponent;

//Character Status
	const int32 MaxHealthPoint = 100;
	const int32 MaxEnergyPoint = 90;
	const int32 MaxShieldPoint = 3;
	const int32 MaxUltimateSkillPoint = 1500;

	int32 CurrentHealthPoint = 100 ;
	int32 CurrentEnergyPoint = 90;
	int32 CurrentShieldPoint = 3;
	int32 CurrentUltimateSkillPoint = 0;

//Attack
	UPROPERTY(EditDefaultsOnly, Category = PlayerSetting)
	TSubclassOf<class ARSS_Projectile_Muriel_Attack1> Attack1_Factory;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* VFX_Spawn_Attack1;
	
	void Excute_Attack1();

	FTransform Calc_AttackTransform();
};
