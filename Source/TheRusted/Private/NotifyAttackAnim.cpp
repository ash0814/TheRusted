// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyAttackAnim.h"
#include "Player_Muriel.h"

void UNotifyAttackAnim::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	APlayer_Muriel* Player = Cast<APlayer_Muriel>(MeshComp->GetOwner());
	if (Player)
	{
		Player->SpawnBullet();
	}
}

void UNotifyAttackAnim::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UNotifyAttackAnim::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
