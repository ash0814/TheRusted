// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_General.h"

ACEnemy_General::ACEnemy_General()
{
	// create skeletal mesh component
	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/SciFi_Robot/MESHES/SCIFI_ROBOT_IK_SK.SCIFI_ROBOT_IK_SK'"));

	if (InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
	}
	

}

void ACEnemy_General::BeginPlay()
{
}

void ACEnemy_General::Tick(float DeltaTime)
{
}

void ACEnemy_General::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void ACEnemy_General::Attack()
{
}

void ACEnemy_General::Die()
{
}
