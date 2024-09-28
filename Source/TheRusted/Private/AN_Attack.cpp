// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Attack.h"

#include "Player_Base.h"

void UAN_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (APlayer_Base* Player = Cast<APlayer_Base>(MeshComp->GetOwner())) {
		Player->Attack();
	}                                                                
}
