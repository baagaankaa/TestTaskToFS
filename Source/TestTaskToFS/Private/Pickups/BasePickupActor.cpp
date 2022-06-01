// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BasePickupActor.h"
#include "Components/SphereComponent.h"

ABasePickupActor::ABasePickupActor()
{
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
    SetRootComponent(MeshComponent);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    CollisionComponent->SetupAttachment(MeshComponent);

}

void ABasePickupActor::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);

	GenerateRotationYaw();	
}

void ABasePickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

	for (APawn* OverlapPawn : OverlappingPawns)
	{
		if (GivePickupTo(OverlapPawn) == false)
		{
			continue;
		}

        PickupWasTaken();
	}
}
void ABasePickupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    APawn* Pawn = Cast<APawn>(OtherActor);

    if (GivePickupTo(Pawn) == true)
    {
        PickupWasTaken();
        return;
    }
    
    if (Pawn != nullptr)
    {
        OverlappingPawns.Add(Pawn);
    }
}

void ABasePickupActor::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    APawn* Pawn = Cast<APawn>(OtherActor);
    OverlappingPawns.Remove(Pawn);
}

bool ABasePickupActor::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ABasePickupActor::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    if (GetRootComponent() != nullptr)
    {
        GetRootComponent()->SetVisibility(false, true);
    }

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABasePickupActor::Respawn, RespawnTime);
}

void ABasePickupActor::Respawn()
{
    GenerateRotationYaw();

    if (GetRootComponent() != nullptr)
    {
        GetRootComponent()->SetVisibility(true, true);
    }

    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ABasePickupActor::GenerateRotationYaw()
{
    const float Direction = FMath::RandBool() 
        ? 1.0f 
        : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

bool ABasePickupActor::CouldBeTaken() const
{
    return GetWorldTimerManager().IsTimerActive(RespawnTimerHandle) == false;
}
