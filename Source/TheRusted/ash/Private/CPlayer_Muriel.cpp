// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/CPlayer_Muriel.h"
#include "../Public/CBullet_Muriel.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

void ACPlayer_Muriel::Attack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && AttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(AttackAnimMontage);
	}
}

void ACPlayer_Muriel::StrongAttack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && StrongAttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(StrongAttackAnimMontage);
	}
}

void ACPlayer_Muriel::Ultimate()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && UltimateAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(UltimateAnimMontage);
	}
	//SpawnBullet();
}



void ACPlayer_Muriel::SpawnBullet()
{


	FTransform _firePosition = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	_firePosition.SetRotation(GetActorForwardVector().Rotation().Quaternion());
	// set rotation to camera forward vector
	//_firePosition.SetRotation(GetControlRotation().Quaternion());
	GetWorld()->SpawnActor<ACBullet_Muriel>(magazine, _firePosition);
	
	//FTransform SocketTransform = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	//FVector Location = SocketTransform.GetLocation();
	//FRotator Rotation = SocketTransform.GetRotation().Rotator();

	//// 방향을 디버그 화살표로 그려보기
	DrawDebugDirectionalArrow(GetWorld(), _firePosition.GetLocation(), _firePosition.GetLocation() + _firePosition.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
}

void ACPlayer_Muriel::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
	currentHP -= amount;
}


void ACPlayer_Muriel::AnyDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Muriel Any Damage"));
	ApplyDamage(Damage);
}


