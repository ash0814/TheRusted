// Fill out your copyright notice in the Description page of Project Settings.


#include "TheRusted/Public/LYM_PBullet.h"

#include "LYM_TestPlayer.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALYM_PBullet::ALYM_PBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// collision
	SphereCollComp = CreateDefaultSubobject<USphereComponent>(TEXT("MainCollidor"));
	SphereCollComp->SetCollisionProfileName(TEXT("BlockAll"));
	SphereCollComp->SetSphereRadius(13);
	RootComponent = SphereCollComp;
	// particle
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MurielAttackBullet"));
	ParticleComp->SetupAttachment(SphereCollComp);
	ParticleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleComp->bAutoActivate = true;
	ParticleComp->bAutoDestroy = true;

	// projectile
	PMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PMovementComp"));
	PMovementComp->SetUpdatedComponent(SphereCollComp);
	
	// InitSpeed
	PMovementComp->InitialSpeed = 3000.f;
	// MaxSpeed
	PMovementComp->MaxSpeed = 5000.f;
	// Bounce
	PMovementComp->bShouldBounce = true;
	// Bounciness
	PMovementComp->Bounciness = 0.3f;
	// gravity
	PMovementComp->ProjectileGravityScale = 0.1f;
}

// Called when the game starts or when spawned
void ALYM_PBullet::BeginPlay()
{
	Super::BeginPlay();
	// death timer
	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void { Destroy(); }), 2.0f, false);
	
	
}

// Called every frame
void ALYM_PBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// hit overlap
void ALYM_PBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		auto player = Cast<ALYM_TestPlayer>(OtherActor);
		if (player)
		{
			return;
		}
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());
	}
	Destroy();
}

