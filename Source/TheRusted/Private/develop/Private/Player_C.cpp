// Fill out your copyright notice in the Description page of Project Settings.


#include "develop/Public/Player_C.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
APlayer_C::APlayer_C()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));
	if (InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
		//GetMesh()->OnComponentHit.AddDynamic(this, &APlayer_C::OnHit);
	}

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	/*SpringArmComp->SetRelativeLocationAndRotation(FVector(110.0f, 100.0f, 60.0f), FRotator(-20.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 530;*/
	SpringArmComp->bUsePawnControlRotation = true;

	SpringArmComp->SetRelativeRotation(FRotator(0, 70, 90));
	SpringArmComp->TargetArmLength = 300;
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	SpringArmComp->SocketOffset = FVector(0.0f, 60.0f, 0.0f);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void APlayer_C::BeginPlay()
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
void APlayer_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayer_C::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Enhanced Input
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &APlayer_C::Move);
		EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &APlayer_C::LookUp);
		EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &APlayer_C::Turn);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &APlayer_C::InputJump);
		EnhancedInputComponent->BindAction(AttackIA, ETriggerEvent::Started, this, &APlayer_C::InputAttack);
		EnhancedInputComponent->BindAction(UltimateIA, ETriggerEvent::Triggered, this, &APlayer_C::InputUltimate);
	}
}

void APlayer_C::Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move"));
	const FVector _CurrentValue = Value.Get<FVector>();
	if (Controller) {
		MoveDirection.X = _CurrentValue.Y;
		MoveDirection.Y = _CurrentValue.X;
	}

	MoveDirection = FTransform(GetControlRotation()).TransformVector(MoveDirection);
	AddMovementInput(MoveDirection);
	MoveDirection = FVector::ZeroVector;
}

void APlayer_C::LookUp(const FInputActionValue& Value)
{
	float _CurrentValue = Value.Get<float>();
	AddControllerPitchInput(_CurrentValue);
}

void APlayer_C::Turn(const FInputActionValue& Value)
{
	float _CurrentValue = Value.Get<float>();
	AddControllerYawInput(_CurrentValue);
}

void APlayer_C::InputJump(const FInputActionValue& Value)
{
	Jump();
}

void APlayer_C::InputAttack(const FInputActionValue& Value)
{
	float _inputValue = Value.Get<float>();
	if (_inputValue > 0.0f)
		Attack();
	else
		StrongAttack();

}

void APlayer_C::InputUltimate(const FInputActionValue& Value)
{
	Ultimate();
}

void APlayer_C::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));
}

void APlayer_C::StrongAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Strong Attack"));
}

void APlayer_C::Ultimate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Ultimate"));
}

float APlayer_C::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	return 0.0f;
}

