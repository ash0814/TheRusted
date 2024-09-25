// Fill out your copyright notice in the Description page of Project Settings.


#include "RSS_Enemy_Normal_Healer.h"
#include "Components/CapsuleComponent.h"

ARSS_Enemy_Normal_Healer::ARSS_Enemy_Normal_Healer()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.0f);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/SciFi_Robot/MESHES/SCIFI_ROBOT_IK_SK.SCIFI_ROBOT_IK_SK'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));

	SetMaterial(0, TEXT("/Script/Engine.Material'/Game/SciFi_Robot/MATERIALS/BODY/PARAMEDIC_MAT.PARAMEDIC_MAT'"));
	SetMaterial(2, TEXT("/Script/Engine.Material'/Game/SciFi_Robot/MATERIALS/DECALS/DECAL_PARAM_MAT.DECAL_PARAM_MAT'"));
}
