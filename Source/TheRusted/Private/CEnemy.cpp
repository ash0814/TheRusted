// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy took damage!"));
	// effect particle
	// damage effect initialization
	UParticleSystem* DamageEffect = LoadObject<UParticleSystem>(nullptr, TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMuriel/FX/Particles/Abilities/Primary/FX/P_Muriel_Primary_HitWorld.P_Muriel_Primary_HitWorld'"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageEffect, GetActorLocation(), FRotator::ZeroRotator, true);
	return 0.0f;
}

