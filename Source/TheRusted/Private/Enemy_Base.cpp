// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Base.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TheRustedGameModeBase.h"

AEnemy_Base::AEnemy_Base()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemy_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ret = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	auto GameMode = Cast<ATheRustedGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->AddPlayerUltimateGauge(30.0);
	}
	return ret;
}

void AEnemy_Base::Attack()
{
	
}

FTransform AEnemy_Base::Calc_AttackTransform(FName socketName, float AttackRange)
{
	FHitResult Hit;
	FVector StartLocation = GetMesh()->GetSocketLocation(socketName);
	FVector EndLocation = StartLocation + GetArrowComponent()->GetForwardVector() * AttackRange;
	//StartLocation
	FRotator LookAtRotator;
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, 5.f, 0, 2.f);
	bool result = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
	if (result)
	{
		LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartLocation, Hit.ImpactPoint);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Start: %s, End: %s, LookAt: %s"), *StartLocation.ToString(), *EndLocation.ToString(), *LookAtRotator.ToString()));
	}
	else
	{
		LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Start: %s, End: %s, LookAt: %s"), *StartLocation.ToString(), *EndLocation.ToString(), *LookAtRotator.ToString()));
	}
	return UKismetMathLibrary::MakeTransform(StartLocation, LookAtRotator);
}
