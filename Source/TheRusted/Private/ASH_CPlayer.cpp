// Fill out your copyright notice in the Description page of Project Settings.


#include "ASH_CPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
AASH_CPlayer::AASH_CPlayer()
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
	/*SpringArmComp->SetRelativeLocationAndRotation(FVector(110.0f, 100.0f, 60.0f), FRotator(-20.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 530;*/
	SpringArmComp->bUsePawnControlRotation = true;

	SpringArmComp->SetRelativeRotation(FRotator(0, 70, 90));
	SpringArmComp->TargetArmLength = 150;
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	SpringArmComp->SocketOffset = FVector(0.0f, 60.0f, 0.0f);

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
void AASH_CPlayer::BeginPlay()
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
void AASH_CPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AASH_CPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Enhanced Input
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &AASH_CPlayer::Move);
		EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &AASH_CPlayer::LookUp);
		EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &AASH_CPlayer::Turn);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &AASH_CPlayer::InputJump);
		EnhancedInputComponent->BindAction(AttackIA, ETriggerEvent::Started, this, &AASH_CPlayer::InputAttack);
		EnhancedInputComponent->BindAction(UltimateIA, ETriggerEvent::Triggered, this, &AASH_CPlayer::InputUltimate);
	}
}

void AASH_CPlayer::Move(const FInputActionValue& Value)
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

void AASH_CPlayer::LookUp(const FInputActionValue& Value)
{
	float _CurrentValue = Value.Get<float>();
	AddControllerPitchInput(_CurrentValue);
}

void AASH_CPlayer::Turn(const FInputActionValue& Value)
{
	float _CurrentValue = Value.Get<float>();
	AddControllerYawInput(_CurrentValue);
}

void AASH_CPlayer::InputJump(const FInputActionValue& Value)
{
	Jump();
}

void AASH_CPlayer::InputAttack(const FInputActionValue& Value)
{
	float _inputValue = Value.Get<float>();
	if (_inputValue > 0.0f)
		Attack();
	else
		StrongAttack();

}

void AASH_CPlayer::InputUltimate(const FInputActionValue& Value)
{
	Ultimate();
}

void AASH_CPlayer::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));
}

void AASH_CPlayer::StrongAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Strong Attack"));
}

void AASH_CPlayer::Ultimate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Ultimate"));
}

float AASH_CPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	return 0.0f;
}

