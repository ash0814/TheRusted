// Fill out your copyright notice in the Description page of Project Settings.


#include "ash/Public/CBullet_Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ash/Public/CPlayer_Muriel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACBullet_Enemy::ACBullet_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollComp = CreateDefaultSubobject<USphereComponent>(TEXT("AMainCollider"));
	SphereCollComp->SetCollisionProfileName("BlockAllDynamic");
	SphereCollComp->SetSphereRadius(10);
	RootComponent = SphereCollComp;

	PMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	PMovementComp->SetUpdatedComponent(SphereCollComp);
	PMovementComp->InitialSpeed = 5000;
	PMovementComp->MaxSpeed = 5000;
	PMovementComp->bShouldBounce = true;
	PMovementComp->Bounciness = 0.3f;

	// spawn particle
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EnemyAttackBullet"));
	ParticleComp->SetupAttachment(SphereCollComp);
	ParticleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleComp->bAutoActivate = true;
	ParticleComp->bAutoDestroy = true;
}

// Called when the game starts or when spawned
void ACBullet_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBullet_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FTimerHandle deathTimer;
	// GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &APBullet::Die, 3.0f, false);
	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void { Destroy(); }), 3.0f, false);

}

void ACBullet_Enemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());
	}
	Die();
}

void ACBullet_Enemy::Die()
{
	Destroy();
}

