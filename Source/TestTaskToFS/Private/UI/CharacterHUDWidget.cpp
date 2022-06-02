// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterHUDWidget.h"
#include "Components/WeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWidget, All, All);

FString UCharacterHUDWidget::GetBulletAmountFormat(bool& HasAmmo)
{
	UWeaponComponent* WeaponComponent = GetCharacterComponent<UWeaponComponent>();
	
	FAmmo Ammo;

	if (WeaponComponent == nullptr || WeaponComponent->GetCurrentAmmo(Ammo) == false)
	{
		HasAmmo = false;
		return FString();
	}

	int32 CurrentAmmoAmount = Ammo.GetCurrentAmmoData().Bullets;
	int32 AllAmmoAmount = Ammo.GetDefaultAmmoData().Bullets * Ammo.GetCurrentAmmoData().Clips;

	HasAmmo = true;
	return GetFormatBullet(CurrentAmmoAmount, AllAmmoAmount);
}

float UCharacterHUDWidget::GetReloadProcessPercent(bool& InReloadProgress)
{
	if (GetWorld() == nullptr)
	{
		InReloadProgress = false;
		return 0.0f;
	}

	UWeaponComponent* WeaponComponent = GetCharacterComponent<UWeaponComponent>();

	if (WeaponComponent == nullptr)
	{
		InReloadProgress = false;
		return 0.0f;
	}

	float ProgressPercent;
	InReloadProgress = WeaponComponent->GetReloadProgress(ProgressPercent);

	return ProgressPercent;
}

FString UCharacterHUDWidget::GetFormatBullet(int32 CurrentAmount, int32 MaxAmount)
{
	const int32 MaxLen = 3;
	const TCHAR PrefixSymbol = '0';

	FString BulletStr = FString::FromInt(CurrentAmount);
	//const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

	//if (SymbolsNumToAdd > 0)
	//{
		//BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
	//}

	return BulletStr;
}


template<typename T>
T* UCharacterHUDWidget::GetCharacterComponent()
{
	AActor* SomeActor = GetOwningPlayerPawn();

	if (SomeActor == nullptr)
	{
		return nullptr;
	}

	return Cast<T>(SomeActor->GetComponentByClass(T::StaticClass()));
}