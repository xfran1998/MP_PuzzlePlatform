// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority()){
        SetReplicates(true); // Set this platform to replicate
        SetReplicateMovement(true); // Set the platform movement to replicate

        StartPos = GetActorLocation();

        // convert FinalPos to global space
        FinalPos = GetTransform().TransformPosition(FinalPos);
        NormalTravel = (FinalPos - StartPos).GetSafeNormal();
        MaxDistance = (FinalPos - StartPos).Size();

        // Triky change so platforms don't start moving at the start of the game without using a boolean extra variable
        ChangeSpeed();
        ChangeEndPoints();
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!HasAuthority()) return;

    MovePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(const float &DeltaTime)
{
    if(!bIsMoving) return;

    if (HasArrived())
    {
        SetActorLocation(FinalPos); // avoid overshooting the target
        bIsMoving = false;
    }
    else
    {
        FVector NextPos = GetNextLocation(DeltaTime);
        SetActorLocation(NextPos);
    }
}

bool AMovingPlatform::HasArrived() const
{
    return (GetActorLocation() - StartPos).Size() >= MaxDistance;
}

FVector AMovingPlatform::GetNextLocation(const float &DeltaTime) const
{
    FVector ActualPos = GetActorLocation();
    return ActualPos + DeltaTime * Speed * NormalTravel;
}


void AMovingPlatform::ChangeSpeed()
{
    NormalTravel = -NormalTravel;
}

void AMovingPlatform::ChangeEndPoints()
{
    FVector aux = FinalPos;
    FinalPos = StartPos;
    StartPos = aux;
}

void AMovingPlatform::SetMovement(bool bHasToMove)
{
    ChangeSpeed();
    ChangeEndPoints();

    bIsMoving = true;
}