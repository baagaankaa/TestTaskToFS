// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickupActor.h"
#include "AmmoPickup.generated.h"

class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class TESTTASKTOFS_API AAmmoPickup : public ABasePickupActor
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	int32 ClipsAmount;

protected:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
