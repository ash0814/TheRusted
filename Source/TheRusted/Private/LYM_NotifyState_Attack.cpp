// Fill out your copyright notice in the Description page of Project Settings.


#include "LYM_NotifyState_Attack.h"

void ULYM_NotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	tpsPlayer = Cast<ALYM_TestPlayer>(MeshComp->GetOwner());

	if(tpsPlayer)
	{
		tpsPlayer->SpawnBullet();
	}
}

void ULYM_NotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "NotifyTick");
}

void ULYM_NotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "NotifyEnd");
}
