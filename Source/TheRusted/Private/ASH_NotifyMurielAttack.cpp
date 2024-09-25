// Fill out your copyright notice in the Description page of Project Settings.


#include "ASH_NotifyMurielAttack.h"
#include "Player_Muriel.h"

void UASH_NotifyMurielAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	APlayer_Muriel* player = Cast<APlayer_Muriel>(MeshComp->GetOwner());
	if (player)
	{
		player->Attack();
	}
}

void UASH_NotifyMurielAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UASH_NotifyMurielAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
