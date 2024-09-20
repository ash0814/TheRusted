// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_Attack.h"

void UNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	tpsPlayer = Cast<ATestPlayer>(MeshComp->GetOwner());

	if(tpsPlayer)
	{
		tpsPlayer->SpawnBullet();
	}
}

void UNotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "NotifyTick");
}

void UNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "NotifyEnd");
}
