// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickupActor.h"
#include "WeaponPickup.generated.h"

class ABaseWeapon;
class USkeletalMeshComponent;
/**
 * 
 */
UCLASS()
class TESTTASKTOFS_API AWeaponPickup : public ABasePickupActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Values");
	TSubclassOf<ABaseWeapon> Weapon;

protected:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
