// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoSystem.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmo, All, All);

void AmmoSystem::SetDefault(FAmmoData Ammo, ABaseWeapon* Weapon)
{
	DefaultAmmo = Ammo;
	CurrentAmmo = DefaultAmmo;

	TargetWeapon = Weapon;
}

bool AmmoSystem::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool AmmoSystem::IsAmmoEmpty() const
{
	return  CurrentAmmo.Infinite == false && 
			CurrentAmmo.Clips == 0 &&
			RemaindeBullets == 0 &&
			IsClipEmpty() == true;
}

bool AmmoSystem::IsAmmoFull() const
{
	return  CurrentAmmo.Clips == DefaultAmmo.Clips && 
			CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool AmmoSystem::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && (CurrentAmmo.Clips > 0 || RemaindeBullets > 0);
}

bool AmmoSystem::DecreaseBullet()
{
	SetBullet(CurrentAmmo.Bullets - 1);

	if (IsClipEmpty() == true && IsAmmoEmpty() == false)
	{
		OnClipEmptied.Broadcast(TargetWeapon);
		return true;
	}

	return false;
}

void AmmoSystem::SetBullet(int Amount)
{
	CurrentAmmo.Bullets = FMath::Clamp(Amount, 0, DefaultAmmo.Bullets);
}

void AmmoSystem::SetFullBullet()
{
	SetBullet(DefaultAmmo.Bullets);
}

void AmmoSystem::SetRemaineBullet(int Amount)
{
	RemaindeBullets = FMath::Clamp(Amount, 0, DefaultAmmo.Bullets * DefaultAmmo.Clips);

	if (RemaindeBullets / DefaultAmmo.Bullets > 0)
	{
		RemaindeBullets -= DefaultAmmo.Bullets;
		CurrentAmmo.Clips++;
	}
}

void AmmoSystem::ChangeClip()
{
	if (CurrentAmmo.Infinite == true)
	{
		SetFullBullet();
		return;
	}

	if (IsAmmoEmpty() == true)
	{
		return;
	}

	SetRemaineBullet(RemaindeBullets + CurrentAmmo.Bullets);

	if (CurrentAmmo.Clips == 0)
	{
		SetBullet(RemaindeBullets);
		SetRemaineBullet(0);
		return;
	}

	CurrentAmmo.Clips--;
	SetFullBullet();
}

int32 AmmoSystem::GetAllBullets()
{
	return DefaultAmmo.Bullets * CurrentAmmo.Clips + RemaindeBullets;
}

bool AmmoSystem::TryAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite == true || IsAmmoFull() == true || ClipsAmount <= 0)
	{
		return false;
	}

	if (IsAmmoEmpty() == true)
	{
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmptied.Broadcast(TargetWeapon);
		return true;
	}

	if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const int32 NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;

		CurrentAmmo.Clips = DefaultAmmo.Clips - NextClipsAmount >= 0
			? NextClipsAmount
			: DefaultAmmo.Clips;
	}

	SetFullBullet();
	return true;
}
