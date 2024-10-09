// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_CantAttack.h"

#include "Enemy_Base.h"

void UANS_CantAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (AEnemy_Base* Enemy = Cast<AEnemy_Base>(MeshComp->GetOwner()))
	{
		Enemy->bCanAttack = false;
	}
}

void UANS_CantAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AEnemy_Base* Enemy = Cast<AEnemy_Base>(MeshComp->GetOwner()))
	{
		Enemy->bCanAttack = true;
	}
}
