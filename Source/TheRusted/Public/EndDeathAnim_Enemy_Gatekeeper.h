// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndDeathAnim_Enemy_Gatekeeper.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API UEndDeathAnim_Enemy_Gatekeeper : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
