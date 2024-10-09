// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

UCLASS()
class THERUSTED_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TMap<FName, UAudioComponent*> SoundMap;

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void AddSound(const FName SoundName, USoundBase* SoundAsset);
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlaySound(const FName SoundName);
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void StopSound(const FName SoundName);
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void StopAllSounds();
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void SetVolume(const FName SoundName, float Volume);
};
