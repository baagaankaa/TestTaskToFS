// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ammo/AmmoSystem.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartReloadSignature, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASKTOFS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;

private:
	bool ReloadInProgress = false;

	FTimerHandle ReloadProgressHandle;


public:	
	UWeaponComponent();

	FOnStartReloadSignature OnStartReload;

	void StartFire();
	void StopFire();
	void ReloadWeapon();

	bool TrySetWeapon(TSubclassOf<ABaseWeapon> WeaponType);
	bool TryAddClips(int32 Amount);

	bool GetCurrentAmmo(AmmoSystem*& Ammo);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void OnClipEmpty(ABaseWeapon* ClipEmptyWeapon);

	void DestroyCurrentWeapon();
	void ChangeClip();

	void ReloadEnded();
	bool CanReload() const;
};
