// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterHUDWidget.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/ProgressBar.h"
#include "Components/WeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWidget, All, All);

void UCharacterHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	UWeaponComponent* WeaponComponent = GetCharacterComponent<UWeaponComponent>();

	if (WeaponComponent == nullptr)
	{
		return;
	}

	ReloadProgressElement = new ReloadProgressBarElement(ReloadProgressBar);
	WeaponComponent->OnStartReload.AddUObject(this, &UCharacterHUDWidget::OnStartReload);
}

void UCharacterHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	ReloadProgressElement->Tick(InDeltaTime);
}

FString UCharacterHUDWidget::GetBulletAmountFormat(bool& HasAmmo)
{
	UWeaponComponent* WeaponComponent = GetCharacterComponent<UWeaponComponent>();
	
	AmmoSystem* Ammo;

	if (WeaponComponent == nullptr || WeaponComponent->GetCurrentAmmo(Ammo) == false)
	{
		HasAmmo = false;
		return FString();
	}

	int32 CurrentAmmoAmount = Ammo->GetCurrentAmmoData().Bullets;
	int32 AllAmmoAmount = Ammo->GetAllBullets();

	HasAmmo = true;
	return GetFormatBullet(CurrentAmmoAmount, AllAmmoAmount);
}


FString UCharacterHUDWidget::GetFormatBullet(int32 CurrentAmount, int32 MaxAmount)
{
	return FString::FromInt(CurrentAmount).AppendChar('/').Append(FString::FromInt(MaxAmount));
}

void UCharacterHUDWidget::OnStartReload(float Duration)
{
	ReloadProgressElement->OnStartReload(Duration);
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