// Fill out your copyright notice in the Description page of Project Settings.


#include "BeginAttackNotify.h"
#include "Player_Base.h"
#include "Enemy_Gatekeeper.h"

void UBeginAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (APlayer_Base* Player = Cast<APlayer_Base>(MeshComp->GetOwner())) {
		Player->Attack();
	}
	else if (AEnemy_Gatekeeper* gk = Cast<AEnemy_Gatekeeper>(MeshComp->GetOwner())) {
		gk->SpawnBullet();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("SpawnBulletGateKeeper"));
	}
}
