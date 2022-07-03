// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformLoop.h"

AMovingPlatformLoop::AMovingPlatformLoop()
{
    
}

void AMovingPlatformLoop::BeginPlay()
{
    Super::BeginPlay();

    // if (HasAuthority()){
    //     SetReplicates(true); // Set this platform to replicate
    //     SetReplicateMovement(true); // Set the platform movement to replicate

    //     StartPos = GetActorLocation();

    //     // convert FinalPos to global space
    //     // finalPos += StartPos;
    //     FinalPos = GetTransform().TransformPosition(FinalPos);

    //     NormalTravel = (FinalPos - StartPos).GetSafeNormal();

    //     MaxDistance = (FinalPos - StartPos).Size();
    // }
}

void AMovingPlatformLoop::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // if (!HasAuthority()) return;

    // MovePlatform(DeltaTime);
}

void AMovingPlatformLoop::MovePlatform(const float &DeltaTime)
{
    if (!bIsMoving) return;

    if (HasArrived())
    {
        ChangeSpeed();
        ChangeEndPoints();
    }
    else
    {
        FVector NextPos = GetNextLocation(DeltaTime);
        SetActorLocation(NextPos);
    }
}

void AMovingPlatformLoop::SetMovement(bool bHasToMove)
{
    bIsMoving = bHasToMove;
    UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *GetName());
}

