// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyMurielAttack.h"
#include "Player_Muriel.h"

void UNotifyMurielAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	APlayer_Muriel* player = Cast<APlayer_Muriel>(MeshComp->GetOwner());
	if (player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Attack"));
		player->SpawnBullet();
	}
}

void UNotifyMurielAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UNotifyMurielAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
