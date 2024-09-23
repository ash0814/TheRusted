// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_Base.generated.h"

UCLASS()
class THERUSTED_API ACharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//Util
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComp;
	
	UAnimInstance* AnimInstance;
	
	FTransform Calc_AttackTransform(FName socketName);
	void MontagePlay(UAnimMontage* animMontage);
	void SetSkeletalMesh(const TCHAR* ObjectToFind);
};
