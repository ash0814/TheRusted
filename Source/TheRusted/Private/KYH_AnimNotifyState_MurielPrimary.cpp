// Fill out your copyright notice in the Description page of Project Settings.


#include "KYH_AnimNotifyState_MurielPrimary.h"

#include "KYH_CustomPlayerBase.h"

void UKYH_AnimNotifyState_MurielPrimary::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                     float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	Player = Cast<AKYH_CustomPlayerBase>(MeshComp->GetOwner());
	if(Player)
	{
		Player->_SpawnPrimary();
	}
}

void UKYH_AnimNotifyState_MurielPrimary::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UKYH_AnimNotifyState_MurielPrimary::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
