
#include "Player_Muriel_C.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

void APlayer_Muriel_C::Attack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && AttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(AttackAnimMontage);
	}
}

void APlayer_Muriel_C::StrongAttack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && StrongAttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(StrongAttackAnimMontage);
	}
}

void APlayer_Muriel_C::Ultimate()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && UltimateAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(UltimateAnimMontage);
	}
	//SpawnBullet();
}



void APlayer_Muriel_C::SpawnBullet()
{
	/*
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

	*/
}

void APlayer_Muriel_C::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
}