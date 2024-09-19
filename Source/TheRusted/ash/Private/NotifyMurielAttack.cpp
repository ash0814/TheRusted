// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/NotifyMurielAttack.h"
#include "../Public/CPlayer_Muriel.h"

void UNotifyMurielAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ACPlayer_Muriel* player = Cast<ACPlayer_Muriel>(MeshComp->GetOwner());
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
