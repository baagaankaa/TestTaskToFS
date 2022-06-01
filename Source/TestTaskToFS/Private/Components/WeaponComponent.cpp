// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "GameFramework/Character.h"
#include "FAmmo.h"


UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::StartFire()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->StopFire();
}

bool UWeaponComponent::TrySetWeapon(TSubclassOf<ABaseWeapon> Weapon)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (Character == nullptr || GetWorld() == nullptr)
	{
		return false;
	}

	ABaseWeapon* SpawnedWeapon = GetWorld()->SpawnActor<ABaseWeapon>(Weapon);

	if (SpawnedWeapon == nullptr)
	{
		return false;
	}
	
	DestroyCurrentWeapon();

	SpawnedWeapon->GetAmmo().OnClipEmptied.AddUObject(this, &UWeaponComponent::OnClipEmpty);
	SpawnedWeapon->SetOwner(Character);
	
	CurrentWeapon = SpawnedWeapon;

	AttachWeaponToSocket(SpawnedWeapon, Character->GetMesh(), WeaponEquipSocketName);
	return true;
}


void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (Weapon == nullptr || SceneComponent == nullptr)
	{
		return;
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::OnClipEmpty(ABaseWeapon* ClipEmptyWeapon)
{
	if (ClipEmptyWeapon == nullptr)
	{
		return;
	}

	if (CurrentWeapon == ClipEmptyWeapon)
	{
		ChangeClip();
	}
}

void UWeaponComponent::DestroyCurrentWeapon()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentWeapon->Destroy();

	CurrentWeapon = nullptr;
}

void UWeaponComponent::ChangeClip()
{
	if (CanReload() == false || GetWorld() == nullptr)
	{
		return;
	}

	CurrentWeapon->StopFire();
	GetWorld()->GetTimerManager()
		.SetTimer(ReloadProgressHandle, this, &UWeaponComponent::ReloadEnded, CurrentWeapon->GetReloadSeconds(), false);
}

void UWeaponComponent::ReloadEnded()
{
	GetWorld()->GetTimerManager().ClearTimer(ReloadProgressHandle);

	ReloadInProgress = false;
	CurrentWeapon->ChangeClip();
}

bool UWeaponComponent::CanReload() const
{
	return CurrentWeapon != nullptr && ReloadInProgress == false && CurrentWeapon->CanReload();
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyCurrentWeapon();
	Super::EndPlay(EndPlayReason);
}
