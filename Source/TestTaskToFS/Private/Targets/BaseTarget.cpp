// Fill out your copyright notice in the Description page of Project Settings.


#include "Targets/BaseTarget.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogTarget, All, All);

ABaseTarget::ABaseTarget()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
	TextComponent->SetupAttachment(MeshComponent); 
}

void ABaseTarget::BeginPlay()
{
	Super::BeginPlay();

	check(MeshComponent);
	check(TextComponent);

	TimerEnded();
	OnTakeAnyDamage.AddDynamic(this, &ABaseTarget::OnTakeDamage);
}

void ABaseTarget::OnTakeDamage(
	AActor* Actor, float Damage, const UDamageType* DamageType, AController* Controller, AActor* DamageCauser)
{
	GetWorldTimerManager().ClearTimer(TextVisibilityTimer);
	GetWorldTimerManager().SetTimer(TextVisibilityTimer, this, &ABaseTarget::TimerEnded, TextVisibilityDuration, false);

	TextComponent->SetText(FText::FromString(FString::SanitizeFloat(Damage)));
	TextComponent->SetVisibility(true);
}

void ABaseTarget::TimerEnded()
{
	TextComponent->SetVisibility(false);
}

