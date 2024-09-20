// Fill out your copyright notice in the Description page of Project Settings.


#include "ash/Public/CEnemy_General.h"
#include "ash/Public/CBullet_Enemy.h"
#include "ash/Public/CPlayer_Muriel.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ACEnemy_General::ACEnemy_General()
{
	// create skeletal mesh component
	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ash/Blueprint/SCIFI_ROBOT_IK_SK_ash.SCIFI_ROBOT_IK_SK_ash'"));

	if (InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
	}
	

}

void ACEnemy_General::BeginPlay()
{
	Super::BeginPlay();
	// set the default value of dropItemID
	dropItemID = 0;
	// set the default value of magazine
	//magazine = ACBullet_Enemy::StaticClass();
}

void ACEnemy_General::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACEnemy_General::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACEnemy_General::Attack()
{
	FTransform _fireTransform = GetMesh()->GetSocketTransform(FName("headSocket"));
	FVector _fireDirection = _fireTransform.GetRotation().GetForwardVector();
	FVector _fireLocation = _fireTransform.GetLocation();
	GetWorld()->SpawnActor<ACBullet_Enemy>(ACBullet_Enemy::StaticClass(), _fireLocation, _fireDirection.Rotation());
}

void ACEnemy_General::Die()
{
}
