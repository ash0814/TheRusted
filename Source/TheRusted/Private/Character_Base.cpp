// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Base.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACharacter_Base::ACharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacter_Base::SetSkeletalMesh(const TCHAR* ObjectToFind)
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(ObjectToFind);
	if (InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-90),FRotator(0,-90,0));
	}
}

void ACharacter_Base::MontagePlay(UAnimMontage* animMontage)
{
	if(animMontage == nullptr)
		return;
	
	if(AnimInstance)
	{		
		AnimInstance->Montage_Play(animMontage);
	}
	else
	{		
		AnimInstance = GetMesh()->GetAnimInstance();
		MontagePlay(animMontage);
	}
}

FTransform ACharacter_Base::Calc_AttackTransform(FName socketName)
{
	const float AttackRange = 20000;
	FHitResult Hit;
	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * AttackRange;
	
	bool result = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
	FVector AttackPosition = GetMesh()->GetSocketLocation(socketName);
	FRotator LookAtRotator;
	if(result)
	{		
		LookAtRotator = UKismetMathLibrary::FindLookAtRotation(AttackPosition,Hit.ImpactPoint);
	}
	else
	{
		LookAtRotator = UKismetMathLibrary::FindLookAtRotation(AttackPosition,EndLocation);
	}
	return UKismetMathLibrary::MakeTransform(AttackPosition, LookAtRotator);
}


