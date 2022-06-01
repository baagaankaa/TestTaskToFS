// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

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

	void StartFire();
	void StopFire();

	bool TrySetWeapon(TSubclassOf<ABaseWeapon> Weapon);

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
