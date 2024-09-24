// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheRustedGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API ATheRustedGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
private:
	bool bCanStoreOpen = false;
	bool bIsStoreOpen = false;

public:
	UFUNCTION(BlueprintCallable)
	void SetCanStoreOpen(bool bCanOpen);
	UFUNCTION(BlueprintCallable)
	bool GetCanStoreOpen() { return bCanStoreOpen; }
	UFUNCTION(BlueprintCallable)
	bool GetIsStoreOpen() { return bIsStoreOpen; }
	UFUNCTION(BlueprintCallable)
	void SetIsStoreOpen(bool bIsOpen) { bIsStoreOpen = bIsOpen; }
};
