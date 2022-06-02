// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo/AmmoSystem.h"
#include "BaseWeapon.generated.h"


UCLASS()
class TESTTASKTOFS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	float GetReloadSeconds() const { return SecondsToReload; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo {15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = "0.01"))
	float SecondsToReload = 0.75f;

	bool FireInProgress = false;

	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();

private:
	AmmoSystem* Ammo = nullptr;
	
public:	
	ABaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

	virtual bool CanFire(bool ReloadInProgress);

	AmmoSystem* GetAmmo() const { return Ammo; }
	void ChangeClip();
	bool CanReload();

protected:
	virtual void BeginPlay() override;

	

};
