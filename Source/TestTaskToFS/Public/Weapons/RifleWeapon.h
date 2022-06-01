// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASKTOFS_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float SecondsBetweenShots = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = "5.0", ClampMax = "100.0"))
	FVector2D DamageRange{10.0f, 35.0f};

private:
	FTimerHandle ShotTimerHandle;

public:
	virtual void StartFire() override;
	virtual void StopFire() override;


protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	AController* GetController() const;

private:
	void MakeDamage(const FHitResult& HitResult);
	float GetDamage() const;
};
