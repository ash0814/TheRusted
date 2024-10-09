// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API UEndAttackNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	EPlayerMovementState NewMovementState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	EPlayerActionState NewActionState;
};
