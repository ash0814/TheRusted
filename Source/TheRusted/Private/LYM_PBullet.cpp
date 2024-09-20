// Fill out your copyright notice in the Description page of Project Settings.


#include "TheRusted/Public/LYM_PBullet.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ALYM_PBullet::ALYM_PBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollComp = CreateDefaultSubobject<USphereComponent>(TEXT("MainCollidor"));
	SphereCollComp->SetCollisionProfileName(TEXT("BlockAll"));
	SphereCollComp->SetSphereRadius(13);
	RootComponent = SphereCollComp;

	SMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SMeshComp->SetupAttachment(SphereCollComp);
	SMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 발사체 컴포넌트 생성
	PMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PMovementComp"));
	// 발사체 컴포넌트를 Update 시킬 대상(컴포넌트) 지정
	PMovementComp->SetUpdatedComponent(SphereCollComp);
	// 초기속도
	PMovementComp->InitialSpeed = 3000.f;
	// 최대속도
	PMovementComp->MaxSpeed = 5000.f;
	// 반동
	PMovementComp->bShouldBounce = true;
	// 반동크기
	PMovementComp->Bounciness = 0.3f;
}

// Called when the game starts or when spawned
void ALYM_PBullet::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle deathTimer;

	GetWorld()->GetTimerManager().SetTimer(deathTimer,FTimerDelegate::CreateLambda([this]()->void{Destroy();}),2.0f,false);
	
	
}

// Called every frame
void ALYM_PBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

