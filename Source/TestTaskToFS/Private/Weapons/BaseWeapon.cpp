// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(MeshComponent);


	//CurrentAmmo.SetDefault(DefaultAmmo);
}

void ABaseWeapon::StartFire()
{
	FireInProgress = true;
}

void ABaseWeapon::StopFire()
{
	FireInProgress = true;
}

void ABaseWeapon::MakeShot(){}

bool ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (GetPlayerViewPoint(ViewLocation, ViewRotation) == false)
	{
		return false;
	}

	const FVector ShootDirection = ViewRotation.Vector();

	TraceStart = ViewLocation;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

bool ABaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (Character == nullptr)
	{
		return false;
	}

	const APlayerController* Controller = Character->GetController<APlayerController>();

	if (Controller == nullptr)
	{
		return false;
	}

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ABaseWeapon::GetMuzzleWorldLocation() const
{
	return MeshComponent->GetSocketLocation(MuzzleSocketName);
}

void ABaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (GetWorld() == nullptr)
	{
		return;
	}

	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = true;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->
		LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, 
			ECollisionChannel::ECC_Visibility, CollisionParams);
}
