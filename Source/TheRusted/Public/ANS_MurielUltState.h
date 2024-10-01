// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Muriel.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ANS_MurielUltState.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API UANS_MurielUltState : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	EMurielUltState NewUltState;
};
