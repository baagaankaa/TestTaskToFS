// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BaseGameMode.h"
#include "Characters/BaseCharacter.h"

ABaseGameMode::ABaseGameMode()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
}