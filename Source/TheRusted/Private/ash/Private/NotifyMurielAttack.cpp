// Fill out your copyright notice in the Description page of Project Settings.


#include "ash/Public/NotifyMurielAttack.h"
#include "ash/Public/CPlayer_Muriel.h"
#include "develop/Public/Player_Muriel_C.h"

void UNotifyMurielAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	APlayer_Muriel_C* player = Cast<APlayer_Muriel_C>(MeshComp->GetOwner());
	if (player)
	{
		player->SpawnBullet();
	}
}

void UNotifyMurielAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UNotifyMurielAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
