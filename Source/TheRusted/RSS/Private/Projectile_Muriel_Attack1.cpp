// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Projectile_Muriel_Attack1.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile_Muriel_Attack1::AProjectile_Muriel_Attack1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);

	SetLifeSpan(2);
}

// Called when the game starts or when spawned
void AProjectile_Muriel_Attack1::BeginPlay()
{
	Super::BeginPlay();	
	UGameplayStatics::SpawnEmitterAttached(VFX_Projectile, RootComponent);	
	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFX_Fire, GetActorLocation(), GetActorRotation());
}

// Called every frame
void AProjectile_Muriel_Attack1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * 500 * DeltaTime, true);
}

void AProjectile_Muriel_Attack1::DestroyProjectile()
{	
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_NoHit, GetActorLocation(), GetActorRotation());

	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_Hit_Character, GetActorLocation(), GetActorRotation());

	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_Hit_Wolrd, GetActorLocation(), GetActorRotation());

	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_Hit_Water, GetActorLocation(), GetActorRotation());
}
