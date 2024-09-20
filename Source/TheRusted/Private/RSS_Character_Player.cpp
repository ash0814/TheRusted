// Fill out your copyright notice in the Description page of Project Settings.


#include "RSS_Character_Player.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "RSS_Projectile_Muriel_Attack1.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARSS_Character_Player::ARSS_Character_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));
	if(tempSkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempSkeletalMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-100), FRotator(0,-90,0));
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocationAndRotation(FVector(0,0,50),FRotator(-20,0,0));
	SpringArmComponent->TargetArmLength = 530;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;

	GetCharacterMovement()->MaxWalkSpeed = 500;
	JumpMaxCount = 1;
	JumpMaxHoldTime = 0.1;
}

// Called when the game starts or when spawned
void ARSS_Character_Player::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			LocalPlayerSubsystem->AddMappingContext(IMC_Player, 0);
		}
	}
}

// Called every frame
void ARSS_Character_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARSS_Character_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerInput)
	{
		PlayerInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ARSS_Character_Player::Input_Move);
		PlayerInput->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ARSS_Character_Player::Input_Turn);
		PlayerInput->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &ARSS_Character_Player::Input_LookUp);
		PlayerInput->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ARSS_Character_Player::Input_Jump);
		PlayerInput->BindAction(IA_Attack1, ETriggerEvent::Started, this, &ARSS_Character_Player::Input_Attack1);
		PlayerInput->BindAction(IA_Attack2, ETriggerEvent::Started, this, &ARSS_Character_Player::Input_Attack2);
		PlayerInput->BindAction(IA_Skill1, ETriggerEvent::Started, this, &ARSS_Character_Player::Input_Skill1);
	}
}

void ARSS_Character_Player::Input_Move(const FInputActionValue& inputValue)
{
	FVector value = inputValue.Get<FVector>();

	MoveDirection = FTransform(GetControlRotation()).TransformVector(value);;
	AddMovementInput(MoveDirection);
	MoveDirection = FVector::ZeroVector;	
}

void ARSS_Character_Player::Input_Turn(const struct FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();

	AddControllerYawInput(value);
}

void ARSS_Character_Player::Input_LookUp(const struct FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();

	if(bIsInvertLookUp)
		value *= -1;

	AddControllerPitchInput(value);
}

void ARSS_Character_Player::Input_Jump(const struct FInputActionValue& inputValue)
{
	Jump();
}

void ARSS_Character_Player::Input_Attack1(const struct FInputActionValue& inputValue)
{
	MontagePlay(AM_Attack1);
	Excute_Attack1();
	
}

void ARSS_Character_Player::Input_Attack2(const struct FInputActionValue& inputValue)
{
	MontagePlay(AM_Attack2);
	Excute_Attack1();
}

void ARSS_Character_Player::Input_Skill1(const struct FInputActionValue& inputValue)
{
	MontagePlay(AM_Skill1);
	Excute_Attack1();
}

void ARSS_Character_Player::MontagePlay(UAnimMontage* animMontage)
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

void ARSS_Character_Player::Excute_Attack1()
{	
	UGameplayStatics::SpawnEmitterAttached(VFX_Spawn_Attack1, GetMesh(), FName("Muzzle_01"));
	GetWorld()->SpawnActor<ARSS_Projectile_Muriel_Attack1>(Attack1_Factory, Calc_AttackTransform());
}

FTransform ARSS_Character_Player::Calc_AttackTransform()
{
	FHitResult Hit;
	FVector StartLocation = CameraComponent->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComponent->GetForwardVector() * 20000;
	FTransform AttackTransform;

	bool result = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
	FVector S = GetMesh()->GetSocketLocation(FName("WeaponAttachPointR"));
	if(result)
	{		
		FVector T = Hit.ImpactPoint;
		FRotator R = UKismetMathLibrary::FindLookAtRotation(S,T);
		AttackTransform = UKismetMathLibrary::MakeTransform(S, R);
	}
	else
	{
		FRotator R = UKismetMathLibrary::FindLookAtRotation(S,EndLocation);
		AttackTransform = UKismetMathLibrary::MakeTransform(S, R);
	}

	return AttackTransform;
}
	


