// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Base.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "InteractableInterface.h"


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

	bCanMove = true;

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

	FTimerHandle TraceTimerHandle;
	GetWorldTimerManager().SetTimer(TraceTimerHandle, this, &APlayer_Base::PerformInteractionTrace, 0.2f, true);

	CurrentCoin = 1000;
	QuickSlot.Add(EItemType::Heath, 0);
	QuickSlot.Add(EItemType::Energy, 0);
	QuickSlot.Add(EItemType::Shield, 0);
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
		EnhancedInputComponent->BindAction(IA_Attack_Ultimate, ETriggerEvent::Triggered, this, &APlayer_Base::Input_Attack_Ultimate);
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &APlayer_Base::InputInteract);
	}
}

void APlayer_Base::Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move"));
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

void APlayer_Base::InputInteract(const FInputActionValue& Value)
{
	if (Value.Get<float>() > 0.0f) {
		if (CachedInteractableActor) {
			IInteractableInterface* InteractableActor = Cast<IInteractableInterface>(CachedInteractableActor);
			if (InteractableActor) {
				InteractableActor->Interact();
			}
		}
	}
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	return 0.0f;
}

FTransform APlayer_Base::Calc_AttackTransform(FName socketName, float AttackRange)
{
	FHitResult Hit;
	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * AttackRange;

	bool result = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
	FVector AttackPosition = GetMesh()->GetSocketLocation(socketName);
	FRotator LookAtRotator;
	if (result)
	{
		LookAtRotator = UKismetMathLibrary::FindLookAtRotation(AttackPosition, Hit.ImpactPoint);
	}
	else
	{
		LookAtRotator = UKismetMathLibrary::FindLookAtRotation(AttackPosition, EndLocation);
	}
	return UKismetMathLibrary::MakeTransform(AttackPosition, LookAtRotator);
}

void APlayer_Base::PerformInteractionTrace()
{
	FVector _Start = GetActorLocation();
	FVector _End = GetActorLocation() + GetActorForwardVector() * 500.0f;
	FHitResult _HitOut;

	FCollisionQueryParams _TraceParams;
	_TraceParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(_HitOut, _Start, _End, ECC_GameTraceChannel2, _TraceParams);

	if (bHit) {
		AActor* HitActor = _HitOut.GetActor();
		if (HitActor) {
			IInteractableInterface* InteractableActor = Cast<IInteractableInterface>(HitActor);
			if (InteractableActor) {
				if (CachedInteractableActor != HitActor) {
					if (CachedInteractableActor) {
						IInteractableInterface* CachedInteractable = Cast<IInteractableInterface>(CachedInteractableActor);
						if (CachedInteractable) {
							CachedInteractable->HideInteractionWidget();
						}
					}
					CachedInteractableActor = HitActor;
					InteractableActor->DisplayInteractionWidget();
				}
				//InteractableActor->Interact();
			}
		}
	}
	else {
		if (CachedInteractableActor) {
			IInteractableInterface* CachedInteractable = Cast<IInteractableInterface>(CachedInteractableActor);
			if (CachedInteractable) {
				CachedInteractable->HideInteractionWidget();
			}
			CachedInteractableActor = nullptr;
		}
	}
}

int32 APlayer_Base::GetCoin() const
{
	return CurrentCoin;
}

void APlayer_Base::UpdateCoin(int32 value)
{
	CurrentCoin += value;
}

void APlayer_Base::AddItemToQuickSlot(EItemType ItemType)
{
	if (QuickSlot.Contains(ItemType)) {
		QuickSlot[ItemType]++;
	}
	else {
		// Error
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("QuickSlot Error"));
	}
}
