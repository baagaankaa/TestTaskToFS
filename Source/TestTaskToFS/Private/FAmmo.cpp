// Fill out your copyright notice in the Description page of Project Settings.


#include "FAmmo.h"


void FAmmo::SetDefault(FAmmoData Ammo, ABaseWeapon* TargetWeapon)
{
	DefaultAmmo = Ammo;
	CurrentAmmo = DefaultAmmo;

	this->Weapon = TargetWeapon;
}

bool FAmmo::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool FAmmo::IsAmmoEmpty() const
{
	return CurrentAmmo.Infinite == false && CurrentAmmo.Clips == 0 && IsClipEmpty() == true;
}

bool FAmmo::IsAmmoFull() const
{
	return  CurrentAmmo.Clips == DefaultAmmo.Clips && 
			CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool FAmmo::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets&& CurrentAmmo.Clips > 0;
}

bool FAmmo::DecreaseBullet()
{
	SetBullet(CurrentAmmo.Bullets - 1);

	if (IsClipEmpty() == true && IsAmmoEmpty() == false)
	{
		OnClipEmptied.Broadcast(Weapon);
		return true;
	}

	return false;
}

void FAmmo::SetBullet(int Amount)
{
	CurrentAmmo.Bullets = FMath::Clamp(Amount, 0, DefaultAmmo.Bullets);
}

void FAmmo::SetFullBullet()
{
	SetBullet(DefaultAmmo.Bullets);
}

void FAmmo::ChangeClip()
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

	CurrentAmmo.Clips--; 
	SetFullBullet();
}

bool FAmmo::TryAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite == true || IsAmmoFull() == true || ClipsAmount <= 0)
	{
		return false;
	}

	if (IsAmmoEmpty() == true)
	{
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmptied.Broadcast(Weapon);
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
