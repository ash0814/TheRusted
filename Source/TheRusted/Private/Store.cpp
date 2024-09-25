// Fill out your copyright notice in the Description page of Project Settings.


#include "Store.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStore::AStore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	SetRootComponent(BoxComp);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FocusCamera"));
	CameraComp->SetRelativeLocation(FVector(330.0f, 0.0f, 60.0f));
	CameraComp->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	CameraComp->SetupAttachment(RootComponent);
	Skeletal = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal"));
	Skeletal->SetupAttachment(RootComponent);

	InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidgetComponent"));
	InteractionWidgetComponent->SetupAttachment(Skeletal);

	InteractionWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 220.0f));
	InteractionWidgetComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	InteractionWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	InteractionWidgetComponent->SetDrawSize(FVector2D(50.0f, 50.0f));

	if (InteractionWidgetClass != nullptr)
	{
		InteractionWidgetComponent->SetWidgetClass(InteractionWidgetClass);
	}
}

// Called when the game starts or when spawned
void AStore::BeginPlay()
{
	Super::BeginPlay();
	InteractionWidgetComponent->SetVisibility(false);

}

// Called every frame
void AStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStore::DisplayInteractionWidget()
{
	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(true);
	}
}

void AStore::HideInteractionWidget()
{
	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(false);
	}
}

void AStore::Interact()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(this, 1.0f);
	OurPlayerController->SetInputMode(FInputModeGameAndUI());
	OurPlayerController->SetShowMouseCursor(true);

	HideInteractionWidget();
}

