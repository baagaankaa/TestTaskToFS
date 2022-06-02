// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Elements/ReloadProgressBarElement.h"
#include "CharacterHUDWidget.generated.h"

class UProgressBar;
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

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ReloadProgressBar;

private:
	ReloadProgressBarElement* ReloadProgressElement = nullptr;

protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	template <typename T>
	T* GetCharacterComponent();

	FString GetFormatBullet(int32 CurrentAmount, int32 MaxAmount);
	void OnStartReload(float Duration);
};