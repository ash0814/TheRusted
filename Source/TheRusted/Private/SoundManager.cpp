// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"

#include "Components/AudioComponent.h"


// Sets default values
ASoundManager::ASoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoundManager::AddSound(const FName SoundName, USoundBase* SoundAsset)
{
	if(!SoundAsset) return;

	if(SoundMap.Contains(SoundName)) return;

	if(UAudioComponent* Audiocomp = NewObject<UAudioComponent>(this))
	{
		Audiocomp->bAutoActivate = false;
		Audiocomp->SetupAttachment(RootComponent);
		Audiocomp->SetSound(SoundAsset);
		Audiocomp->RegisterComponent();
		SoundMap.Add(SoundName, Audiocomp);
	}
}

void ASoundManager::PlaySound(const FName SoundName)
{
	if(UAudioComponent** FoundSound = SoundMap.Find(SoundName))
	{
		if(*FoundSound && !(*FoundSound)->IsPlaying())
		{
			(*FoundSound)->Play();
		}
	}
}

void ASoundManager::StopSound(const FName SoundName)
{
	if(UAudioComponent** FoundSound = SoundMap.Find(SoundName))
	{
		if(*FoundSound && (*FoundSound)->IsPlaying())
		{
			(*FoundSound)->Stop();
		}
	}
}

void ASoundManager::StopAllSounds()
{
	for (auto& Sound : SoundMap)
	{
		if(Sound.Value)
		{
			Sound.Value->Stop();
		}
	}
}

void ASoundManager::SetVolume(const FName SoundName, float Volume)
{
	if(UAudioComponent** FoundSound = SoundMap.Find(SoundName))
	{
		if(*FoundSound)
		{
			(*FoundSound)->SetVolumeMultiplier(Volume);
		}
	}
}