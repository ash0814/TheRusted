// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Base.h"

#include "Enemy_Base.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "InteractableInterface.h"

#define QHealth 0
#define QEnergy 1
#define QShield 2
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

	FTimerHandle TraceTimerHandle;
	GetWorldTimerManager().SetTimer(TraceTimerHandle, this, &APlayer_Base::PerformInteractionTrace, 0.2f, true);

	CurrentCoin = 1000;
	QuickSlot.Add(0);
	QuickSlot.Add(0);
	QuickSlot.Add(0);
}

// Called every frame
void APlayer_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetTargetEnemy();
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
		EnhancedInputComponent->BindAction(IA_QuickSlot, ETriggerEvent::Started, this, &APlayer_Base::InputQuickSlot);
	}
}

void APlayer_Base::SetPlayerMovementState(EPlayerMovementState NewMovementState)
{
	if(PlayerMovementState == NewMovementState) return;

	PlayerMovementState = NewMovementState;
	HandleMovementState();
}

void APlayer_Base::SetPlayerActionState(EPlayerActionState NewActionState)
{
	PlayerActionState = NewActionState;
	HandleActionState();
}

void APlayer_Base::SetCombatState(ECombatState NewCombatState)
{
	if(PlayerCombatState == NewCombatState) return;

	PlayerCombatState = NewCombatState;
}

void APlayer_Base::HandleMovementState()
{
	switch (PlayerMovementState)
	{
	case EPlayerMovementState::Idle:
		// 캐릭터가 Idle 상태일 때 처리할 로직
			break;
	case EPlayerMovementState::Moving:
		// 캐릭터가 걷는 중일 때 처리할 로직
			break;
	case EPlayerMovementState::Jumping:
		// 점프 중일 때 처리할 로직
			Jump();
		break;
	case EPlayerMovementState::Dashing:
		// 대쉬 중일 때 처리할 로직
			break;
	case EPlayerMovementState::Falling:
		// 낙하 중일 때 처리할 로직
			break;
	case EPlayerMovementState::Stopped:
		// 캐릭터가 움직일 수 없을 때 처리할 로직
			break;
	}
}

void APlayer_Base::HandleActionState()
{
	switch (PlayerActionState)
	{
	case EPlayerActionState::None:
		// 기본 상태로 아무 행동도 하지 않을 때
			break;
	case EPlayerActionState::Attack_Primary:
		// 기본 공격 중일 때 로직
			Attack_Primary();
		break;
	case EPlayerActionState::Attack_Strong:
		// 특수 공격 중일 때 로직
			Attack_Strong();
		break;
	case EPlayerActionState::Charging_Ultimate:
		//  궁극기 차징 중일 때 로직
			Charge_Ultimate();
			break;
	case EPlayerActionState::Attack_Ultimate:
		// 궁극기 공격 중일 때 로직
			Attack_Ultimate();
			break;
	case EPlayerActionState::Dead:
		// 캐릭터가 죽었을 때 로직
			break;
	}
}

void APlayer_Base::Move(const FInputActionValue& Value)
{
	if(PlayerMovementState == EPlayerMovementState::Idle || PlayerMovementState == EPlayerMovementState::Moving)
	{
		SetPlayerMovementState(EPlayerMovementState::Moving);
		const FVector _CurrentValue = Value.Get<FVector>();
		if(_CurrentValue == FVector::ZeroVector)
		{
			SetPlayerMovementState(EPlayerMovementState::Idle);
			return;
		}
		if (Controller) {
			MoveDirection.X = _CurrentValue.X;
			MoveDirection.Y = _CurrentValue.Y;
		}

		MoveDirection = FTransform(GetControlRotation()).TransformVector(MoveDirection);
		AddMovementInput(MoveDirection);
		MoveDirection = FVector::ZeroVector;
	}
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
	SetPlayerMovementState(EPlayerMovementState::Jumping);
}

void APlayer_Base::InputInteract(const FInputActionValue& Value)
{
	if (Value.Get<float>() > 0.0f) {
		if (CachedInteractableActor) {
			IInteractableInterface* InteractableActor = Cast<IInteractableInterface>(CachedInteractableActor);
			if (InteractableActor) {
				SetPlayerMovementState(EPlayerMovementState::Stopped);
				InteractableActor->Interact();
			}
		}
	}
}

void APlayer_Base::InputQuickSlot(const FInputActionValue& Value)
{
	int32 _Index = Value.Get<float>();
	switch (_Index)
	{
		case 1:
			if (QuickSlot[QHealth] > 0) {
				QuickSlot[QHealth]--;
				UseHPItem();
			}
			break;
		case 2:
			if (QuickSlot[QEnergy] > 0) {
				QuickSlot[QEnergy]--;
				UseEPItem();
			}
			break;
		case 3:
			if (QuickSlot[QShield] > 0) {
				QuickSlot[QShield]--;
				UseSPItem();
			}
			break;
		default:
			break;
	}
}

void APlayer_Base::Input_Attack_Primary(const FInputActionValue& Value)
{
	if(PlayerActionState == EPlayerActionState::Charging_Ultimate)
	{
		SetPlayerActionState(EPlayerActionState::Attack_Ultimate);
		return;
	}
	if (PlayerActionState == EPlayerActionState::None || PlayerActionState == EPlayerActionState::Attack_Primary)
	{
		if(PlayerMovementState != EPlayerMovementState::Stopped && PlayerMovementState != EPlayerMovementState::Dashing)
		{
			SetPlayerActionState(EPlayerActionState::Attack_Primary);
		}
	}
}

void APlayer_Base::Input_Attack_Strong(const FInputActionValue& Value)
{
	if(PlayerActionState == EPlayerActionState::Charging_Ultimate)
	{
		SetPlayerActionState(EPlayerActionState::None);
		SetPlayerMovementState(EPlayerMovementState::Idle);
		Cancle_Ultimate();
		return;
	}
	if(PlayerActionState == EPlayerActionState::None)
	{
		if(PlayerMovementState != EPlayerMovementState::Stopped && PlayerMovementState != EPlayerMovementState::Dashing)
		{
			SetPlayerActionState(EPlayerActionState::Attack_Strong);
			SetPlayerMovementState(EPlayerMovementState::Stopped);
		}
	}
}

void APlayer_Base::Input_Attack_Ultimate(const FInputActionValue& Value)
{
	if(bCanUltimate && PlayerActionState == EPlayerActionState::None)
	{
		if(PlayerMovementState != EPlayerMovementState::Stopped && PlayerMovementState != EPlayerMovementState::Dashing)
		{
			SetPlayerActionState(EPlayerActionState::Charging_Ultimate);
			SetPlayerMovementState(EPlayerMovementState::Stopped);
		}
		bCanUltimate = false;
	}
}

void APlayer_Base::Attack_Primary()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Attack"));
}

void APlayer_Base::Attack_Strong()
{
	if (BasicStatus.EP >= 30)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Strong Attack"));
		BasicStatus.AddEP(-30);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Not Enough Energy"));
	}
}

void APlayer_Base::Charge_Ultimate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Chargeing Ultimate"));
}

void APlayer_Base::Cancle_Ultimate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ultimate Cancled"));
}

void APlayer_Base::Attack_Ultimate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Attack Ultimate"));
}

void APlayer_Base::Attack()
{
	
}

float APlayer_Base::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//SetPlayerMovementState(EPlayerMovementState::Stopped);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TakeDamage"));
	return 0.0f;
}

FTransform APlayer_Base::Calc_AttackTransform(FName socketName, float AttackRange)
{
	FHitResult Hit;
	FVector StartLocation = GetMesh()->GetSocketLocation(socketName);
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * AttackRange;
	bool result = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Pawn);
	if (result)
	{
		EndLocation = Hit.ImpactPoint;

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("hit Actor name: %s"), *Hit.GetActor()->GetName()));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Start: %s, End: %s, LookAt: %s"), *StartLocation.ToString(), *EndLocation.ToString(), *LookAtRotator.ToString()));
	}
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, 5.f, 0, 2.f);
	//DrawDebugLine(GetWorld(), EndLocation, EndLocation + FVector(0, 0, EndLocation.Z + AttackRange), FColor::Red, true, 5.f, 0, 20.f);
	return UKismetMathLibrary::MakeTransform(StartLocation, LookAtRotator);
}

void APlayer_Base::SetTargetEnemy()
{
	FHitResult Hit;
	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + CameraComp->GetForwardVector() * 10000;
	bool result = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Pawn);

	if (result)
	{
		auto enemy = Cast<AEnemy_Base>(Hit.GetActor());

		if(enemy)
		{
			TargetEnemy = enemy;
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("TargetEnemy name: %s"), *Hit.GetActor()->GetName()));
		}
	}
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

bool APlayer_Base::CheckCanBuy(int32 value)
{
	return (CurrentCoin >= value);
}

void APlayer_Base::AddItemToQuickSlot(EItemType ItemType)
{
	if (ItemType == EItemType::Heath)
		QuickSlot[0]++;
	else if (ItemType == EItemType::Energy)
		QuickSlot[1]++;
	else if (ItemType == EItemType::Shield)
		QuickSlot[2]++;
}

void APlayer_Base::UseHPItem()
{
	BasicStatus.AddHP(100);
}

void APlayer_Base::UseEPItem()
{
	BasicStatus.AddEP(100);
}

void APlayer_Base::UseSPItem()
{
	BasicStatus.AddSP(1);
}

void APlayer_Base::ChargeUltimateGauge(float amount)
{
	BasicStatus.AddULTGauge(amount);
	if (BasicStatus.ULTGauge >= BasicStatus.MaxULTGauge)
	{
		bCanUltimate = true;
	}
	else {
		bCanUltimate = false;
	}
}
