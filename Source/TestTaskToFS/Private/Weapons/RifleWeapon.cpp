// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RifleWeapon.h"


void ARifleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ARifleWeapon::StartFire()
{
	Super::StartFire();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, SecondsBetweenShots, true);
	MakeShot();
}

void ARifleWeapon::StopFire()
{
	Super::StopFire();

	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ARifleWeapon::MakeShot()
{
	if (GetWorld() == nullptr || GetAmmo()->IsAmmoEmpty() == true)
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (GetTraceData(TraceStart, TraceEnd) == false)
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit == true)
	{
		MakeDamage(HitResult);
	}

	DecreaseAmmo();
}

bool ARifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (GetPlayerViewPoint(ViewLocation, ViewRotation) == false) 
	{
		return false;
	}

	const float HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);

	TraceStart = ViewLocation;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

AController* ARifleWeapon::GetController() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	return Pawn == nullptr
		? nullptr
		: Pawn->GetController();
}

void ARifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	AActor* DamagedActor = HitResult.GetActor();

	if (DamagedActor == nullptr)
	{
		return;
	}

	FPointDamageEvent PointDamageEvent;
	PointDamageEvent.HitInfo = HitResult;
	DamagedActor->TakeDamage(GetDamage(), PointDamageEvent, GetController(), this);
}

float ARifleWeapon::GetDamage() const
{
	return FMath::RandRange(DamageRange.X, DamageRange.Y);
}
