// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_Muriel_Attack.h"

#include "Player_Base.h"

void UANS_Muriel_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration)
{
	//Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	APlayer_Base* player = Cast<APlayer_Base>(MeshComp->GetOwner());
	if (player)
	{
		player->Attack();
	}
}
