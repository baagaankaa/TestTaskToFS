// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::StartFire()
{
}

void UWeaponComponent::StopFire()
{
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}
