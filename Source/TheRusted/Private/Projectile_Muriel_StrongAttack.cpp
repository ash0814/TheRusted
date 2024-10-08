// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Muriel_StrongAttack.h"

#include "Enemy_Base.h"
#include "Player_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AProjectile_Muriel_StrongAttack::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if(OtherActor == nullptr)
		return;
	
	if(OtherComp == nullptr)
		return;
	
	if(OtherActor->IsA(APlayer_Base::StaticClass()))
		return;
	
	bHit = true;
	
	if(OtherActor->IsA(AEnemy_Base::StaticClass()))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 20.0f, GetInstigatorController(), this, UDamageType::StaticClass());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_HitCharacter, Hit.ImpactPoint, UKismetMathLibrary::MakeRotFromZ(Hit.ImpactNormal));
	}
	else
	{
		UGameplayStatics::ApplyDamage(OtherActor, 20.0f, GetInstigatorController(), this, UDamageType::StaticClass());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_HitWorld, Hit.ImpactPoint, UKismetMathLibrary::MakeRotFromZ(Hit.ImpactNormal));
	}
	
	Destroy();
}
