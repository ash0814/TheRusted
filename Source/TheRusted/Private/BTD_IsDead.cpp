// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_IsDead.h"

#include "AIController.h"
#include "Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_IsDead::UBTD_IsDead()
{
	NodeName = TEXT("IsDead");
}

bool UBTD_IsDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto bbc = OwnerComp.GetBlackboardComponent();

	if(bbc == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("bbc is null"));
		return false;
	}

	auto thisCharacter = OwnerComp.GetAIOwner()->GetCharacter();
	if (thisCharacter == nullptr)
		return false;

	AEnemy_Base* enemy = Cast<AEnemy_Base>(thisCharacter);
	if (enemy == nullptr)
		return false;

	if(enemy->isDead)
		bbc->SetValueAsEnum(FName(TEXT("AIState")), 4);
	
	return enemy->isDead;
}
