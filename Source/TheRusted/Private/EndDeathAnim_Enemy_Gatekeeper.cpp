// Fill out your copyright notice in the Description page of Project Settings.


#include "EndDeathAnim_Enemy_Gatekeeper.h"
#include "Enemy_Gatekeeper.h"

void UEndDeathAnim_Enemy_Gatekeeper::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EndDeathAnim"));
	AEnemy_Gatekeeper* _enemy = Cast<AEnemy_Gatekeeper>(MeshComp->GetOwner());
	if (_enemy)
	{
		_enemy->Die();
	}
}
