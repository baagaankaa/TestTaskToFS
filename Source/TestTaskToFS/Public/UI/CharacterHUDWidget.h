// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASKTOFS_API UCharacterHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetBulletAmountFormat(bool& HasAmmo);
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetReloadProcessPercent(bool& InReloadProgress);


private:
	template <typename T>
	T* GetCharacterComponent();

	FString GetFormatBullet(int32 CurrentAmount, int32 MaxAmount);
};