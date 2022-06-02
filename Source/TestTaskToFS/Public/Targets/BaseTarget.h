// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTarget.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;
class UBoxComponent;

UCLASS()
class TESTTASKTOFS_API ABaseTarget : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UTextRenderComponent* TextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float TextVisibilityDuration = 0.5f;

private:
	FTimerHandle TextVisibilityTimer;

public:	
	ABaseTarget();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnTakeDamage(AActor* Actor, float Damage, const class UDamageType* DamageType, 
		class AController* Controller, AActor* DamageCauser);

private:
	void TimerEnded();
};
