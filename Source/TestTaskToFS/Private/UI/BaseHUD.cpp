// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"
#include "Blueprint/UserWidget.h"

void ABaseHUD::BeginPlay()
{
	UUserWidget* CharacterHUDWidget = CreateWidget<UUserWidget>(GetWorld(), CharacterHUDWidgetClass);

	if (CharacterHUDWidget != nullptr)
	{
		CharacterHUDWidget->AddToViewport();
	}
}
