// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer_Muriel.h"
#include "CBullet_Muriel.h"

void ACPlayer_Muriel::Attack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && AttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(AttackAnimMontage);
	}
}

void ACPlayer_Muriel::SpawnBullet()
{
	//WeaponAttachPointR

	FTransform _firePosition = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	_firePosition.SetRotation(GetActorForwardVector().Rotation().Quaternion());
	GetWorld()->SpawnActor<ACBullet_Muriel>(magazine, _firePosition);
	
	//FTransform SocketTransform = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	//FVector Location = SocketTransform.GetLocation();
	//FRotator Rotation = SocketTransform.GetRotation().Rotator();

	//// 방향을 디버그 화살표로 그려보기
	DrawDebugDirectionalArrow(GetWorld(), _firePosition.GetLocation(), _firePosition.GetLocation() + _firePosition.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
}


