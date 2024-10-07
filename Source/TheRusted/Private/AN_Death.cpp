// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Death.h"
#include "Enemy_Base.h"

void UAN_Death::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AEnemy_Base* Enemy = Cast<AEnemy_Base>(MeshComp->GetOwner())) {
		Enemy->Death();
	}   	
}
