// Fill out your copyright notice in the Description page of Project Settings.


#include "TheRusted/Public/CustomPlayerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACustomPlayerBase::ACustomPlayerBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Spring Arm & Camera
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->TargetArmLength = 510.0f;
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 70.0f, 70.0f));
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);

	// Init Movement & Basic Status
	GetCharacterMovement()->JumpZVelocity = 630.0f;
	BasicStatus.InitStatus(FBasicStatus(100.0f, 100.0f, 90.0f, 50.0f, 3, 3, 1500.0f, 0.0f));
}

// Called when the game starts or when spawned
void ACustomPlayerBase::BeginPlay()
{
	Super::BeginPlay();

	//Add Mapping Context (Enhanced Input)
	if(APlayerController* Playercontroller = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Playercontroller->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called every frame
void ACustomPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Status Debugging
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("MaxHP : %.2f\nHP : %.2f\nMaxEP : %.2f\nEP : %.2f\nMaxSP : %d\nSP : %d\nMaxULTGauge : %.2f\nULTGauge : %.2f"), BasicStatus.MaxHP, BasicStatus.HP, BasicStatus.MaxEP, BasicStatus.EP, BasicStatus.MaxSP, BasicStatus.SP, BasicStatus.MaxULTGauge, BasicStatus.ULTGauge));
}

// Called to bind functionality to input
void ACustomPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Enhanced Input Binding
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent && InputMappingContext)
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ACustomPlayerBase::_Move);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &ACustomPlayerBase::_Jump);
		EnhancedInputComponent->BindAction(LookHorizontalIA, ETriggerEvent::Triggered, this, &ACustomPlayerBase::_LookHorizontal);
		EnhancedInputComponent->BindAction(LookVerticalIA, ETriggerEvent::Triggered, this, &ACustomPlayerBase::_LookVertical);
		EnhancedInputComponent->BindAction(PrimaryIA, ETriggerEvent::Started, this, &ACustomPlayerBase::_Primary);
		EnhancedInputComponent->BindAction(SpecialAttackIA, ETriggerEvent::Triggered, this, &ACustomPlayerBase::_SpecialAttack);
		EnhancedInputComponent->BindAction(UltimateIA, ETriggerEvent::Started, this, &ACustomPlayerBase::_Ultimate);
	}
}

void ACustomPlayerBase::_Move(const FInputActionValue& Value)
{
	FVector2D MovementValue = Value.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Cyan, FString::Printf(TEXT("Move x : %.f, y : %.f"), MovementValue.X, MovementValue.Y));
	AddMovementInput(GetActorForwardVector(), MovementValue.Y);
	AddMovementInput(GetActorRightVector(), MovementValue.X);
}

void ACustomPlayerBase::_Jump(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Cyan, FString::Printf(TEXT("Jump")));
	Jump();
}

void ACustomPlayerBase::_LookHorizontal(const FInputActionValue& Value)
{
	float LookHorizontalValue = Value.Get<float>();

	AddControllerYawInput(LookHorizontalValue);
}

void ACustomPlayerBase::_LookVertical(const FInputActionValue& Value)
{
	float LookVerticalValue = Value.Get<float>();

	AddControllerPitchInput(LookVerticalValue);
}

void ACustomPlayerBase::_Primary(const FInputActionValue& Value)
{
	//Primary Attack
}

void ACustomPlayerBase::_SpawnPrimary()
{
	
}

void ACustomPlayerBase::_SpecialAttack(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	if(InputValue)	//Check Value
	{
		//Check is enough EP
		if(BasicStatus.EP >= GetWorld()->GetDeltaSeconds() * EPConsumptionPerSecond)
		{
			BasicStatus.EP -= GetWorld()->GetDeltaSeconds() * EPConsumptionPerSecond * InputValue;
		}
	}
}

void ACustomPlayerBase::_Ultimate(const FInputActionValue& Value)
{
	if(BasicStatus.ULTGauge >= BasicStatus.MaxULTGauge)
	{
		BasicStatus.ULTGauge = 0;
	}
}

