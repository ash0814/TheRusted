// Fill out your copyright notice in the Description page of Project Settings.


#include "BeginAttackNotify.h"
#include "Player_Base.h"

void UBeginAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (APlayer_Base* Player = Cast<APlayer_Base>(MeshComp->GetOwner())) {
		Player->Attack();
	}
}
