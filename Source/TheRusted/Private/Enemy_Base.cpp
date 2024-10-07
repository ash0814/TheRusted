// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Base.h"

#include "AIController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
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

void AEnemy_Base::Death()
{
}

FTransform AEnemy_Base::Calc_AttackTransform(FName socketName, float AttackRange)
{
	FHitResult Hit;
	FVector StartLocation = GetMesh()->GetSocketLocation(socketName);
	FVector EndLocation = StartLocation + GetArrowComponent()->GetForwardVector() * AttackRange;

	AAIController* aiController = GetController<AAIController>();

	if(aiController)
	{
		UBlackboardComponent* bb = aiController->GetBlackboardComponent();
		if(bb)
		{
			UE_LOG(LogTemp, Warning,TEXT("AEnemy_Base::Calc_AttackTransform BlackBoard Checked"));
			AActor* TargetActor = Cast<AActor>(bb->GetValueAsObject(FName(TEXT("TargetActor"))));

			if(TargetActor)
			{
				UE_LOG(LogTemp, Warning,TEXT("AEnemy_Base::Calc_AttackTransform BlackBoard TargetActor : %s"), *TargetActor->GetName());
				EndLocation = TargetActor->GetActorLocation();
			}
		}
	}
	else
	{
		bool result = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
		if (result)
		{
			EndLocation = Hit.ImpactPoint;
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Start: %s, End: %s, LookAt: %s"), *StartLocation.ToString(), *EndLocation.ToString(), *LookAtRotator.ToString()));
		}
	}
	
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	return UKismetMathLibrary::MakeTransform(StartLocation, LookAtRotator);
}
