// Fill out your copyright notice in the Description page of Project Settings.


#include "ASH_CPlayer_Muriel.h"
#include "ASH_CBullet_Muriel.h"
#include "GameFramework/Actor.h"

void AASH_CPlayer_Muriel::Attack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && AttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(AttackAnimMontage);
	}
}

void AASH_CPlayer_Muriel::StrongAttack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && StrongAttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(StrongAttackAnimMontage);
	}
}

void AASH_CPlayer_Muriel::Ultimate()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && UltimateAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(UltimateAnimMontage);
	}
	//SpawnBullet();
}



void AASH_CPlayer_Muriel::SpawnBullet()
{


	FTransform _firePosition = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	_firePosition.SetRotation(GetActorForwardVector().Rotation().Quaternion());
	// set rotation to camera forward vector
	//_firePosition.SetRotation(GetControlRotation().Quaternion());
	GetWorld()->SpawnActor<AASH_CBullet_Muriel>(magazine, _firePosition);
	
	//FTransform SocketTransform = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	//FVector Location = SocketTransform.GetLocation();
	//FRotator Rotation = SocketTransform.GetRotation().Rotator();

	//// ������ ����� ȭ��ǥ�� �׷�����
	DrawDebugDirectionalArrow(GetWorld(), _firePosition.GetLocation(), _firePosition.GetLocation() + _firePosition.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
}

void AASH_CPlayer_Muriel::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
	currentHP -= amount;
}


void AASH_CPlayer_Muriel::AnyDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Muriel Any Damage"));
	ApplyDamage(Damage);
}


