
#include "develop/Public/Player_Muriel_C.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "develop/Public/Bullet_Muriel_C.h"

void APlayer_Muriel_C::BeginPlay()
{
	if (magazines.Num() > 0) {
		magazine = magazines[0];
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Muriel Magazine is Empty"));
	}
}

void APlayer_Muriel_C::Attack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && AttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(AttackAnimMontage);
	}
	magazine = magazines[0];
}

void APlayer_Muriel_C::StrongAttack()
{
	UAnimInstance* _animInstance = GetMesh()->GetAnimInstance();
	if (_animInstance && StrongAttackAnimMontage) {
		// print _animInstance Name
		_animInstance->Montage_Play(StrongAttackAnimMontage);
	}
	magazine = magazines[1];
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
	FTransform _firePosition = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	_firePosition.SetRotation(GetActorForwardVector().Rotation().Quaternion());
	// set rotation to camera forward vector
	//_firePosition.SetRotation(GetControlRotation().Quaternion());
	GetWorld()->SpawnActor<ABullet_Muriel_C>(magazine, _firePosition);

	//FTransform SocketTransform = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	//FVector Location = SocketTransform.GetLocation();
	//FRotator Rotation = SocketTransform.GetRotation().Rotator();

	//// 방향을 디버그 화살표로 그려보기
	DrawDebugDirectionalArrow(GetWorld(), _firePosition.GetLocation(), _firePosition.GetLocation() + _firePosition.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
}

void APlayer_Muriel_C::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
}