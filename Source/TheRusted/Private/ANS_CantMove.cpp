// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_CantMove.h"

#include "Enemy_Base.h"

void UANS_CantMove::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (AEnemy_Base* Enemy = Cast<AEnemy_Base>(MeshComp->GetOwner()))
	{
		Enemy->bCanMove = false;
	}
	
}

void UANS_CantMove::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	Super::NotifyEnd(MeshComp, Animation);
	if (AEnemy_Base* Enemy = Cast<AEnemy_Base>(MeshComp->GetOwner()))
	{
		Enemy->bCanMove = true;
	}
}
