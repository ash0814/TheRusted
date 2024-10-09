// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_ISAimed.h"

#include "AIController.h"
#include "Enemy_Base.h"
#include "Player_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Camera/CameraComponent.h"

UBTD_ISAimed::UBTD_ISAimed()
{
	NodeName = TEXT("IsAimed");
}

bool UBTD_ISAimed::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto bbc = OwnerComp.GetBlackboardComponent();

	if(bbc == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("UBTD_ISAimed: bbc is null"));
		return false;
	}
	auto Target = bbc->GetValueAsObject(FName("TargetActor"));
	if(Target == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("UBTD_ISAimed: TargetActor is null"));
		return false;
	}
	APlayer_Base* player = Cast<APlayer_Base>(Target);
	AEnemy_Base* enemy = Cast<AEnemy_Base>(OwnerComp.GetAIOwner()->GetCharacter());
	if(player == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("UBTD_ISAimed: player is null"));
		return false;
	}
	if(enemy == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("UBTD_ISAimed: enemy is null"));
		return false;
	}
	
	// 두 벡터의 정규화 (방향 벡터)
	FVector NormalizedA = enemy->GetActorLocation() - player->CameraComp->GetComponentLocation();
	NormalizedA.Z = 0;	
	NormalizedA = NormalizedA.GetSafeNormal();
	FVector NormalizedB = player->CameraComp->GetForwardVector();
	NormalizedB.Z = 0;
	NormalizedB = NormalizedB.GetSafeNormal();

	FVector DebugLineLocation = enemy->GetActorLocation();
	DebugLineLocation.Z += 100;
	DrawDebugLine(GetWorld(), DebugLineLocation, -NormalizedA, FColor::Green, true, 0.2f, 0, 1.f);

	DrawDebugLine(GetWorld(), DebugLineLocation, -NormalizedB, FColor::Blue, true, 0.2f, 0, 1.f);
	
	// 두 벡터의 내적 계산
	float DotProduct = FVector::DotProduct(NormalizedA, NormalizedB);

	// 내적을 이용해 각도를 구함 (acosf를 사용하여 라디안 값 반환)
	float AngleRadians = acosf(DotProduct);

	// 라디안을 각도로 변환
	float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);
	UE_LOG(LogTemp, Display, TEXT("AngleDegrees: %f"), AngleDegrees);
	if( AngleDegrees < 3)
		return true;
	
	return false;
}