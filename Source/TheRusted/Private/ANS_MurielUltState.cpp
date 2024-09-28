// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_MurielUltState.h"

void UANS_MurielUltState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(APlayer_Muriel* Muriel = Cast<APlayer_Muriel>(MeshComp->GetOwner()))
	{
		Muriel->SetMurielUltState(NewUltState);
	}
}
