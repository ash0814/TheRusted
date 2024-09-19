// Fill out your copyright notice in the Description page of Project Settings.


#include "develop/Public/Bullet_Muriel_C.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "develop/Public/Player_Muriel_C.h"


// Sets default values
ABullet_Muriel_C::ABullet_Muriel_C()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
void ABullet_Muriel_C::BeginPlay()
{
	Super::BeginPlay();
	SphereCollComp->OnComponentHit.AddDynamic(this, &ABullet_Muriel_C::OnHit);

}

// Called every frame
void ABullet_Muriel_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet_Muriel_C::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		auto player = Cast<APlayer_Muriel_C>(OtherActor);
		if (player)
		{
			return;
		}
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());
	}
	Destroy();
}

