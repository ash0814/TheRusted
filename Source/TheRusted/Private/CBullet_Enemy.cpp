// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet_Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "CPlayer_Muriel.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy Bullet Hit"));
	ApplyDamage(OtherActor);
}

void ACBullet_Enemy::ApplyDamage(AActor* OtherActor)
{
	auto player = Cast<ACPlayer_Muriel>(OtherActor);
	if (player)
	{
		player->ApplyDamage(10);
	}
}

void ACBullet_Enemy::Die()
{
	Destroy();
}

