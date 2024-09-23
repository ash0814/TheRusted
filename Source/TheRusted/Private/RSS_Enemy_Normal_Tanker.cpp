// Fill out your copyright notice in the Description page of Project Settings.


#include "RSS_Enemy_Normal_Tanker.h"
#include "Components/CapsuleComponent.h"

ARSS_Enemy_Normal_Tanker::ARSS_Enemy_Normal_Tanker()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.0f);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/SciFi_Robot/MESHES/SCIFI_ROBOT_IK_SK.SCIFI_ROBOT_IK_SK'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));

	SetMaterial(0, TEXT("/Script/Engine.Material'/Game/SciFi_Robot/MATERIALS/BODY/NAVY_MAT.NAVY_MAT'"));
	SetMaterial(2, TEXT("/Script/Engine.Material'/Game/SciFi_Robot/MATERIALS/DECALS/DECAL_DEFAULT_MAT.DECAL_DEFAULT_MAT'"));
}
