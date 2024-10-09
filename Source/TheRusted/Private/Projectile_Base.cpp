// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Base.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile_Base::AProjectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName(FName("BlockAllDynamic"));
	SphereComp->SetSphereRadius(10);
	SetRootComponent(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->SetUpdatedComponent(SphereComp);
	ProjectileMovementComp->InitialSpeed = 3000;
	ProjectileMovementComp->MaxSpeed = 3000;
	ProjectileMovementComp->bShouldBounce = true;
	ProjectileMovementComp->Bounciness = 0.3f;
	ProjectileMovementComp->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &AProjectile_Base::OnComponentHit);
}

// Called every frame
void AProjectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile_Base::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}
