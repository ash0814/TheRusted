// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_General.h"
#include "CBullet_Enemy.h"
#include "CPlayer_Muriel.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ACEnemy_General::ACEnemy_General()
{
	// create skeletal mesh component
	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Blueprint/SCIFI_ROBOT_IK_SK_ash.SCIFI_ROBOT_IK_SK_ash'"));

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
	// arrow 
	FTransform _firePosition = GetActorTransform();
	// fire position location z + 40
	_firePosition.AddToTranslation(FVector(0.0f, 0.0f, 40.0f));
	GetWorld()->SpawnActor<ACBullet_Enemy>(magazine, _firePosition);
	DrawDebugDirectionalArrow(GetWorld(), _firePosition.GetLocation(), _firePosition.GetLocation() + _firePosition.GetRotation().Vector() * 100.0f, 50.0f, FColor::Red, false, 5.0f);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Enemy Attack"));
}

void ACEnemy_General::Die()
{
}
