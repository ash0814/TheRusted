// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Base.h"

#include "Camera/CameraComponent.h"

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
	}
}

void ACharacter_Base::SetMaterial(int32 ElementIndex,const TCHAR* ObjectToFind)
{
	ConstructorHelpers::FObjectFinder<UMaterialInterface> TempMaterial(ObjectToFind);
	if (TempMaterial.Succeeded())
	{
		GetMesh()->SetMaterial(ElementIndex, TempMaterial.Object);
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