// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Attack.h"

#include "Enemy_Base.h"

void UAN_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (AEnemy_Base* Enemy = Cast<AEnemy_Base>(MeshComp->GetOwner())) {
		Enemy->Attack();
	}                                                                
}
