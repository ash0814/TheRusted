// Fill out your copyright notice in the Description page of Project Settings.


#include "KYH_NotifyMurielSpecialAttack.h"

#include "Player_Muriel.h"

void UKYH_NotifyMurielSpecialAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	APlayer_Muriel* player = Cast<APlayer_Muriel>(MeshComp->GetOwner());
	if (player)
	{
		player->Attack();
	}
}

void UKYH_NotifyMurielSpecialAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UKYH_NotifyMurielSpecialAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayer_Muriel* player = Cast<APlayer_Muriel>(MeshComp->GetOwner());
	if (player)
	{
		player->bCanMove = true;
		player->bCanAttack = true;
	}
}