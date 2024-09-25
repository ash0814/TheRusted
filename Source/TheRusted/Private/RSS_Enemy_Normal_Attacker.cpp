// Fill out your copyright notice in the Description page of Project Settings.


#include "RSS_Enemy_Normal_Attacker.h"

#include "Components/CapsuleComponent.h"

ARSS_Enemy_Normal_Attacker::ARSS_Enemy_Normal_Attacker()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.0f);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/SciFi_Robot/MESHES/SCIFI_ROBOT_IK_SK.SCIFI_ROBOT_IK_SK'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));

	SetMaterial(0, TEXT("/Script/Engine.Material'/Game/SciFi_Robot/MATERIALS/BODY/MIL_MAT.MIL_MAT'"));
	SetMaterial(2, TEXT("/Script/Engine.Material'/Game/SciFi_Robot/MATERIALS/DECALS/DECAL_MIL_MAT.DECAL_MIL_MAT'"));
}
