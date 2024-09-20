
#include "develop/Public/Player_Muriel_C.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "develop/Public/Bullet_Muriel_C.h"
#include "Kismet/KismetMathLibrary.h"

void APlayer_Muriel_C::BeginPlay()
{
	Super::BeginPlay();
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

FTransform APlayer_Muriel_C::Calc_AttackTransform()
{
	FHitResult Hit;
	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 20000;
	FTransform AttackTransform;

	bool result = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
	FVector S = GetMesh()->GetSocketLocation(FName("WeaponAttachPointR"));
	if(result)
	{		
		FVector T = Hit.ImpactPoint;
		FRotator R = UKismetMathLibrary::FindLookAtRotation(S,T);
		AttackTransform = UKismetMathLibrary::MakeTransform(S, R);
	}
	else
	{
		FRotator R = UKismetMathLibrary::FindLookAtRotation(S,EndLocation);
		AttackTransform = UKismetMathLibrary::MakeTransform(S, R);
	}

	return AttackTransform;
}

void APlayer_Muriel_C::SpawnBullet()
{
	FTransform _firePosition = Calc_AttackTransform();
	// FTransform _firePosition = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	// _firePosition.SetRotation(GetActorForwardVector().Rotation().Quaternion());
	// set rotation to camera forward vector
	//_firePosition.SetRotation(GetControlRotation().Quaternion());
	GetWorld()->SpawnActor<ABullet_Muriel_C>(magazine, _firePosition);

	//FTransform SocketTransform = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	//FVector Location = SocketTransform.GetLocation();
	//FRotator Rotation = SocketTransform.GetRotation().Rotator();

	//// ������ ����� ȭ��ǥ�� �׷�����
	DrawDebugDirectionalArrow(GetWorld(), _firePosition.GetLocation(), _firePosition.GetLocation() + _firePosition.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);
}

void APlayer_Muriel_C::ApplyDamage(float amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Muriel Apply Damage"));
}