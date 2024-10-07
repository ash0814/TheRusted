// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Healer.h"

#include "NavigationSystemTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile_Healer::AProjectile_Healer()
{
	PrimaryActorTick.bCanEverTick = true;
	// 스피어 콜리전 컴포넌트
	SphereCollComp = CreateDefaultSubobject<USphereComponent>(TEXT("MainCollidor"));
	SphereCollComp->SetCollisionProfileName(TEXT("BlockAll"));
	SphereCollComp->SetSphereRadius(13);
	RootComponent = SphereCollComp;

	// 메쉬 컴포넌트
	SMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SMeshComp->SetupAttachment(SphereCollComp);
	SMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 프로젝타일 컴포넌트
	PMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PMovementComp"));
	PMovementComp->SetUpdatedComponent(SphereCollComp);
	PMovementComp->InitialSpeed = 3000.0f;
	PMovementComp->MaxSpeed = 5000.0f;
	PMovementComp->bShouldBounce = false;
}
