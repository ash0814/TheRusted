// Fill out your copyright notice in the Description page of Project Settings.


#include "TheRusted/Public/TestPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PBullet.h"
#include "TheRusted/TheRusted.h"

// Sets default values
ATestPlayer::ATestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));

	if (InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);
	}
	// SpringArm 초기화, 기본 값 설정
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50),FRotator(-20,0,0));
	SpringArmComp->TargetArmLength = 530;
	SpringArmComp->bUsePawnControlRotation = true;
	// Camera Component 초기화
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext,0);
		}
	}
}

// Called every frame
void ATestPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bind
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA,ETriggerEvent::Triggered,this,&ATestPlayer::Move);
		EnhancedInputComponent->BindAction(LookUpIA,ETriggerEvent::Triggered,this,&ATestPlayer::LookUp);
		EnhancedInputComponent->BindAction(TurnIA,ETriggerEvent::Triggered,this,&ATestPlayer::Turn);
		EnhancedInputComponent->BindAction(JunpIA,ETriggerEvent::Triggered,this,&ATestPlayer::InputJump);
		EnhancedInputComponent->BindAction(AttackIA,ETriggerEvent::Triggered,this,&ATestPlayer::InputAttack);
	}

}

void ATestPlayer::Move(const FInputActionValue& Value)
{
	// 입력 값을 FVector 형태로 가져옴
	const FVector _CurrentValue = Value.Get<FVector>();
	if(Controller)
	{
		//  MoveDirection 벡터에 입력된 X, Y 값을 설정
		MoveDirection.Y = _CurrentValue.X;
		MoveDirection.X = _CurrentValue.Y;
	}
	// 카메라의 현재 회전에 맞춰 MoveDirection을 변환함
	MoveDirection = FTransform(GetControlRotation()).TransformVector(MoveDirection);
	// 변환된 MoveDirection 방향으로 캐릭터를 이동
	AddMovementInput(MoveDirection);
	// MoveDirection을 초기화해 다음 프레임에서 누적되지 않도록 함
	MoveDirection = FVector::ZeroVector;
}

void ATestPlayer::LookUp(const FInputActionValue& Value)
{
	// _CurrentValue를 float형으로 초기화
	float _CurrentValue;
	// isInvertLookUp 이 true 이면
	if(isInvertLookUp)
	{
		// 입력 값을 _CurrentValue에  float형태로 값을 음수로 받아옴
		_CurrentValue = Value.Get<float>() * -1;
	}else
	{
		// 입력 값을 _CurrentValue에 float형태로 값을 받아옴
		_CurrentValue = Value.Get<float>();
	}
	
	// 카메라의 pitch값을 변경하여 위아래 시점 이동을 수행함
	AddControllerPitchInput(_CurrentValue);
}

void ATestPlayer::Turn(const FInputActionValue& Value)
{
	// 입력 값을 float 형태로 가져옴
	const float _CurrentValue = Value.Get<float>();
	// 카메라의 yaw값을 변경하여 위아래 시점 이동을 수행함
	AddControllerYawInput(_CurrentValue);
}

void ATestPlayer::InputJump(const FInputActionValue& Value)
{
	Jump();
}

void ATestPlayer::InputAttack(const FInputActionValue& Value)
{
	FTransform AttackPosition = GetMesh()->GetSocketTransform(TEXT("WeaponAttachPointR"));
	GetWorld()->SpawnActor<APBullet>(magazine,AttackPosition);
}
