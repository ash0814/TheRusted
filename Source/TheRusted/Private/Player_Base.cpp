// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Base.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayer_Base::APlayer_Base()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 70.0f), FRotator(0, 70, 90));
	SpringArmComp->TargetArmLength = 300;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0.0f, 60.0f, 0.0f);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void APlayer_Base::BeginPlay()
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
void APlayer_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayer_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Enhanced Input
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayer_Base::Move);
		EnhancedInputComponent->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &APlayer_Base::LookUp);
		EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &APlayer_Base::Turn);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayer_Base::InputJump);
		EnhancedInputComponent->BindAction(IA_Attack_Primary, ETriggerEvent::Started, this, &APlayer_Base::Input_Attack_Primary);
		EnhancedInputComponent->BindAction(IA_Attack_Strong, ETriggerEvent::Started, this, &APlayer_Base::Input_Attack_Strong);
		EnhancedInputComponent->BindAction(IA_Attack_Ultimate, ETriggerEvent::Started, this, &APlayer_Base::Input_Attack_Ultimate);
	}
}

void APlayer_Base::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Move"));
	const FVector _CurrentValue = Value.Get<FVector>();
	if (Controller) {
		MoveDirection.X = _CurrentValue.X;
		MoveDirection.Y = _CurrentValue.Y;
	}

	MoveDirection = FTransform(GetControlRotation()).TransformVector(MoveDirection);
	AddMovementInput(MoveDirection);
	MoveDirection = FVector::ZeroVector;
}

void APlayer_Base::LookUp(const FInputActionValue& Value)
{
	float _CurrentValue = Value.Get<float>();

	if(bLookUpInvert)
		_CurrentValue *= -1;
	
	AddControllerPitchInput(_CurrentValue);
}

void APlayer_Base::Turn(const FInputActionValue& Value)
{
	float _CurrentValue = Value.Get<float>();
	AddControllerYawInput(_CurrentValue);
}

void APlayer_Base::InputJump(const FInputActionValue& Value)
{
	Jump();
}

void APlayer_Base::Input_Attack_Primary(const FInputActionValue& Value)
{
	Attack_Primary();
}

void APlayer_Base::Input_Attack_Strong(const FInputActionValue& Value)
{
	Attack_Strong();
}

void APlayer_Base::Input_Attack_Ultimate(const FInputActionValue& Value)
{
	Attack_Ultimate();
}

void APlayer_Base::Attack_Primary()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));
}

void APlayer_Base::Attack_Strong()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Strong Attack"));
}

void APlayer_Base::Attack_Ultimate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Ultimate"));
}

void APlayer_Base::Attack()
{
	
}

float APlayer_Base::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	return 0.0f;
}

FTransform APlayer_Base::Calc_AttackTransform(FName socketName)
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
