// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Gatekeeper.h"
#include "Player_Muriel.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile_Gatekeeper::AProjectile_Gatekeeper()
{
}

void AProjectile_Gatekeeper::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &AProjectile_Gatekeeper::OnComponentHit);
}

void AProjectile_Gatekeeper::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Super::OnComponentHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	UGameplayStatics::ApplyDamage(OtherActor, 5.0f, GetInstigatorController(), this, UDamageType::StaticClass());

	Destroy();
}
