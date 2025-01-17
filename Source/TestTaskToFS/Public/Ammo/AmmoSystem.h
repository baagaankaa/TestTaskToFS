// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ammo/FAmmoData.h"
#include "Ammo/AmmoSystem.h"

class ABaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ABaseWeapon*);

class AmmoSystem
{
private:
	int32 RemaindeBullets;

	FAmmoData DefaultAmmo;
	FAmmoData CurrentAmmo;

	ABaseWeapon* TargetWeapon = nullptr;

public:
	void SetDefault(FAmmoData Ammo, ABaseWeapon* Weapon);

	FAmmoData GetCurrentAmmoData() const { return CurrentAmmo; }
	FAmmoData GetDefaultAmmoData() const { return DefaultAmmo; }

	FOnClipEmptySignature OnClipEmptied;

	bool IsClipEmpty() const;
	bool IsAmmoEmpty() const;
	bool IsAmmoFull() const;
	bool CanReload() const;

	bool DecreaseBullet();

	void ChangeClip();
	int32 GetAllBullets();

	bool TryAddAmmo(int32 ClipsAmount);

private:
	void SetBullet(int Amount);
	void SetFullBullet();
	void SetRemaineBullet(int Amount);
};
