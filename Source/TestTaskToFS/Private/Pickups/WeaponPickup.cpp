// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/WeaponPickup.h"
#include "Components/WeaponComponent.h"


bool AWeaponPickup::GivePickupTo(APawn* PlayerPawn) 
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

    return WeaponComponent->TrySetWeapon(Weapon);
}