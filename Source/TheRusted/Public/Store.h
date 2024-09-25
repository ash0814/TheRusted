// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Store.generated.h"

UCLASS()
class THERUSTED_API AStore : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	TSubclassOf<class UUserWidget> InteractionWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	class UWidgetComponent* InteractionWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	TSubclassOf<class UUserWidget> ItemShopWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	class UUserWidget* ItemShopWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* Skeletal;

public:
	virtual void DisplayInteractionWidget() override;
	virtual void HideInteractionWidget() override;
	virtual void Interact() override;
};
