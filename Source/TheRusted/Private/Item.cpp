// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Player_Muriel.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ItemSphere"));
	
	ItemSphere->SetCollisionProfileName("OverlapAll");
	ItemSphere->SetSphereRadius(30);

	ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	
	SetRootComponent(ItemSphere);
	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ItemEffect"));
	ItemEffect->SetupAttachment(ItemSphere);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	auto _player = Cast<APlayer_Muriel>(OtherActor);
	if (_player)
	{
		if (ItemID != 3) {
			_player->AddItemToQuickSlot(ItemID);
		}
		else {
			_player->UpdateCoin(100);
		}
		Destroy();
	}
}

