// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_EnemyCanMoveCheck.h"

#include "AIController.h"
#include "Enemy_Base.h"

UBTD_EnemyCanMoveCheck::UBTD_EnemyCanMoveCheck()
{
	NodeName = TEXT("CanMove");
}

bool UBTD_EnemyCanMoveCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto thisCharacter = OwnerComp.GetAIOwner()->GetCharacter();

	if (thisCharacter == nullptr)
		return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AEnemy_Base* enemy = Cast<AEnemy_Base>(thisCharacter);
	if (enemy == nullptr)
		return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	return enemy->bCanMove;
}
