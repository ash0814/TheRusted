// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_CantMove.h"

#include "Player_Base.h"

void UANS_CantMove::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (APlayer_Base* Player = Cast<APlayer_Base>(MeshComp->GetOwner()))
	{
		Player->bCanMove = false;
	}
	
}

void UANS_CantMove::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (APlayer_Base* Player = Cast<APlayer_Base>(MeshComp->GetOwner()))
	{
		Player->bCanMove = true;
	}
}
