// Fill out your copyright notice in the Description page of Project Settings.


#include "ASH_CBullet_Muriel.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ASH_CPlayer_Muriel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AASH_CBullet_Muriel::AASH_CBullet_Muriel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollComp = CreateDefaultSubobject<USphereComponent>(TEXT("AMainCollider"));
	SphereCollComp->SetCollisionProfileName("BlockAllDynamic");
	SphereCollComp->SetSphereRadius(10);
	RootComponent = SphereCollComp;

	PMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	PMovementComp->SetUpdatedComponent(SphereCollComp);
	PMovementComp->InitialSpeed = 20000;
	PMovementComp->MaxSpeed = 20000;
	PMovementComp->bShouldBounce = true;
	PMovementComp->Bounciness = 0.3f;

	// spawn particle
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MurielAttackBullet"));
	ParticleComp->SetupAttachment(SphereCollComp);
	ParticleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleComp->bAutoActivate = true;
	ParticleComp->bAutoDestroy = true;

}

// Called when the game starts or when spawned
void AASH_CBullet_Muriel::BeginPlay()
{
	Super::BeginPlay();
	SphereCollComp->OnComponentHit.AddDynamic(this, &AASH_CBullet_Muriel::OnHit);
}

// Called every frame
void AASH_CBullet_Muriel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FTimerHandle deathTimer;
	// GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &APBullet::Die, 3.0f, false);
	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void { Destroy(); }), 3.0f, false);

}


void AASH_CBullet_Muriel::Die()
{
	Destroy();
}

void AASH_CBullet_Muriel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		auto player = Cast<AASH_CPlayer_Muriel>(OtherActor);
		if (player)
		{
			return;
		}
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());
	}
	Die();
}

