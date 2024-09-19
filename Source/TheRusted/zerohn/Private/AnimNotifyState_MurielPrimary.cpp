// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AnimNotifyState_MurielPrimary.h"

#include "../Public/CustomPlayerBase.h"

void UAnimNotifyState_MurielPrimary::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                 float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	Player = Cast<ACustomPlayerBase>(MeshComp->GetOwner());
	if(Player)
	{
		Player->_SpawnPrimary();
	}
}

void UAnimNotifyState_MurielPrimary::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_MurielPrimary::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
