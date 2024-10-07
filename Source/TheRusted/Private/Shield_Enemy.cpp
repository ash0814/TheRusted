// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield_Enemy.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AShield_Enemy::AShield_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShieldSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ShieldSphere"));
	ShieldSphere->SetCollisionProfileName("OverlapAll");
	ShieldSphere->SetSphereRadius(100);
	SetRootComponent(ShieldSphere);

	ShieldEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ShieldEffect"));
	// effect scale 
	ShieldEffect->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	ShieldEffect->SetupAttachment(ShieldSphere);

}

// Called when the game starts or when spawned
void AShield_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	// destroy the shield after 5 seconds
	FTimerHandle ShieldTimer;
	GetWorldTimerManager().SetTimer(ShieldTimer, this, &AShield_Enemy::DestroyShield, 5.0f, false);
}

// Called every frame
void AShield_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShield_Enemy::DestroyShield()
{
	Destroy();
}

