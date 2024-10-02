// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_ISAimed.generated.h"

/**
 * 
 */
UCLASS()
class THERUSTED_API UBTD_ISAimed : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_ISAimed();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
