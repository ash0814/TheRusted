// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldComponent.h"
#include "NiagaraComponent.h"
#include "Shield_Enemy.h"
#include "Enemy_base.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UShieldComponent::UShieldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UShieldComponent::SpawnShield()
{
	// make params
	
	if (OwnerCharacter && ShieldClass)
	{
		FVector loc = OwnerCharacter->GetActorLocation();
		FRotator rot = OwnerCharacter->GetActorRotation();
		Shield = GetWorld()->SpawnActor<AShield_Enemy>(ShieldClass, loc, rot);
	}
}


