// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));
	if (InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
		//GetMesh()->OnComponentHit.AddDynamic(this, &ACPlayer::OnHit);
	}

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-20.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 400;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	MaxHP = 100;
	MaxEP = 100;
	MaxSP = 3;
	currentHP = MaxHP;
	currentEP = MaxEP;
	currentSP = MaxSP;
	MaxUltimateGauge = 2000;
	UltimateGauge = 0;
	bCanStrongAttack = true;
	QuickSlot.Push(0);
	QuickSlot.Push(0);
	QuickSlot.Push(0);
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	GetController<APlayerController>()->PlayerCameraManager->ViewPitchMin = -45.0f;
	GetController<APlayerController>()->PlayerCameraManager->ViewPitchMax = 15.0f;
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Enhanced Input
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ACPlayer::Move);
		EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &ACPlayer::LookUp);
		EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &ACPlayer::Turn);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &ACPlayer::InputJump);
		EnhancedInputComponent->BindAction(AttackIA, ETriggerEvent::Started, this, &ACPlayer::InputAttack);
		EnhancedInputComponent->BindAction(UltimateIA, ETriggerEvent::Triggered, this, &ACPlayer::InputUltimate);
	}
}

void ACPlayer::Move(const FInputActionValue& Value)
{
	const FVector _CurrentValue = Value.Get<FVector>();
	if (Controller) {
		MoveDirection.X = _CurrentValue.Y;
		MoveDirection.Y = _CurrentValue.X;
	}

	MoveDirection = FTransform(GetControlRotation()).TransformVector(MoveDirection);
	AddMovementInput(MoveDirection);
	MoveDirection = FVector::ZeroVector;
}

void ACPlayer::LookUp(const FInputActionValue& Value)
{
	float _CurrentValue = Value.Get<float>();
	AddControllerPitchInput(_CurrentValue);
}

void ACPlayer::Turn(const FInputActionValue& Value)
{
	float _CurrentValue = Value.Get<float>();
	AddControllerYawInput(_CurrentValue);
}

void ACPlayer::InputJump(const FInputActionValue& Value)
{
	Jump();
}

void ACPlayer::InputAttack(const FInputActionValue& Value)
{
	float _inputValue = Value.Get<float>();
	if (_inputValue > 0.0f)
		Attack();
	else
		StrongAttack();

}

void ACPlayer::InputUltimate(const FInputActionValue& Value)
{
	Ultimate();
}

void ACPlayer::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));
}

void ACPlayer::StrongAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Strong Attack"));
}

void ACPlayer::Ultimate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Ultimate"));
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	return 0.0f;
}

