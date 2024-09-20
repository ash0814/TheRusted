// Fill out your copyright notice in the Description page of Project Settings.


#include "KYH_PrimaryProjectile.h"

#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AKYH_PrimaryProjectile::AKYH_PrimaryProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile Collision"));
	SetRootComponent(SphereCollisionComp);
	SphereCollisionComp->SetSphereRadius(20.0f);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = SphereCollisionComp;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	// ProjectileMovement->MaxSpeed = ProjectileRange;
	// ProjectileMovement->InitialSpeed = ProjectileRange;

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraComp->SetupAttachment(RootComponent);
	NiagaraComp->SetAutoActivate(false);
	
}

// Called when the game starts or when spawned
void AKYH_PrimaryProjectile::BeginPlay()
{
	Super::BeginPlay();

	if(NiagaraSystem)
	{
		FVector Force = FVector(ProjectileRange, 0.0f, 0.0f);
		NiagaraComp->SetVariableVec3(FName("Target Loc"),Force);
		NiagaraComp->SetAsset(NiagaraSystem);
		NiagaraComp->Activate();
	}
}

// Called every frame
void AKYH_PrimaryProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

