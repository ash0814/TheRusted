// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Grim.h"

#include "Components/CapsuleComponent.h"

AEnemy_Grim::AEnemy_Grim()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(130.0f);
	GetCapsuleComponent()->SetCapsuleRadius(60);
	SetSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGRIMexe/Characters/Heroes/GRIM/Skins/Tier1_5/Wasteland/Meshes/GRIMWasteland.GRIMWasteland'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -130.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void AEnemy_Grim::BeginPlay()
{
	Super::BeginPlay();	
}
