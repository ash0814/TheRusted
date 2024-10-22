// Fill out your copyright notice in the Description page of Project Settings.


#include "EndAttackNotify.h"

void UEndAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (APlayer_Base* Player = Cast<APlayer_Base>(MeshComp->GetOwner())) {
		Player->SetPlayerMovementState(NewMovementState);
		Player->SetPlayerActionState(NewActionState);
	}
}
