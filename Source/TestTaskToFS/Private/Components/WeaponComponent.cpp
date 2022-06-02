// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Ammo/AmmoSystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::StartFire()
{
	if (CurrentWeapon == nullptr || CurrentWeapon->CanFire(ReloadInProgress) == false)
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

void UWeaponComponent::ReloadWeapon()
{
	OnClipEmpty(CurrentWeapon);
}

bool UWeaponComponent::TrySetWeapon(TSubclassOf<ABaseWeapon> WeaponType)
{
	if (CurrentWeapon != nullptr && CurrentWeapon->IsA(WeaponType) == true)
	{
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (Character == nullptr || GetWorld() == nullptr)
	{
		return false;
	}

	ABaseWeapon* SpawnedWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponType);

	if (SpawnedWeapon == nullptr)
	{
		return false;
	}
	
	DestroyCurrentWeapon();

	SpawnedWeapon->GetAmmo()->OnClipEmptied.AddUObject(this, &UWeaponComponent::OnClipEmpty);
	SpawnedWeapon->SetOwner(Character);
	
	CurrentWeapon = SpawnedWeapon;

	AttachWeaponToSocket(SpawnedWeapon, Character->GetMesh(), WeaponEquipSocketName);
	return true;
}

bool UWeaponComponent::TryAddClips(int32 Amount)
{
	if (CurrentWeapon == nullptr)
	{
		return false;
	}

	return CurrentWeapon->GetAmmo()->TryAddAmmo(Amount);
}

bool UWeaponComponent::GetCurrentAmmo(AmmoSystem*& Ammo)
{
	if (CurrentWeapon == nullptr)
	{
		return false;
	}

	Ammo = CurrentWeapon->GetAmmo();
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
	if (ClipEmptyWeapon == nullptr || CurrentWeapon != ClipEmptyWeapon)
	{
		return;
	}

	ChangeClip();
}

void UWeaponComponent::DestroyCurrentWeapon()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->GetAmmo()->OnClipEmptied.RemoveAll(this);
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

	ReloadInProgress = true;

	CurrentWeapon->StopFire();
	GetWorld()->GetTimerManager()
		.SetTimer(ReloadProgressHandle, this, &UWeaponComponent::ReloadEnded, CurrentWeapon->GetReloadSeconds(), false);

	OnStartReload.Broadcast(CurrentWeapon->GetReloadSeconds());
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
