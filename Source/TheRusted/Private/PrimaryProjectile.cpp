// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryProjectile.h"

// Sets default values
APrimaryProjectile::APrimaryProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APrimaryProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrimaryProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

