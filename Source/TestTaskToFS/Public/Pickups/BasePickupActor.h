// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickupActor.generated.h"

class USphereComponent;
class USkeletalMeshComponent;

UCLASS()
class TESTTASKTOFS_API ABasePickupActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;

private:
	float RotationYaw = 0.0f;
	FTimerHandle RespawnTimerHandle;

	UPROPERTY()
	TArray<APawn*> OverlappingPawns;
	
public:	
	ABasePickupActor();

	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual bool GivePickupTo(APawn* PlayerPawn);

private:

	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();
};
