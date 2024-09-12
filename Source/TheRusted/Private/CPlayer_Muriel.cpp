// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer_Muriel.h"

void ACPlayer_Muriel::Attack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && AttackAnimMontage) {
		// print _animInstance Name
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, _animInstance->GetName());
		_animInstance->Montage_Play(AttackAnimMontage);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Muriel Attack"));

}
