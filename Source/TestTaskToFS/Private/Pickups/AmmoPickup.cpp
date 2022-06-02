// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/AmmoPickup.h"
#include "Components/WeaponComponent.h"

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    if (PlayerPawn == nullptr)
    {
        return false;
    }

    UWeaponComponent* WeaponComponent =
        Cast<UWeaponComponent>(PlayerPawn->GetComponentByClass(UWeaponComponent::StaticClass()));

    if (WeaponComponent == nullptr)
    {
        return false;
    }

    return WeaponComponent->TryAddClips(ClipsAmount);
}
