// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatform.h"
#include "MovingPlatformLoop.generated.h"

UCLASS()
class MP_PUZZLEPLATFORM_API AMovingPlatformLoop : public AMovingPlatform
{
	GENERATED_BODY()
	
public:
	AMovingPlatformLoop();

    virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void MovePlatform(const float &DeltaTime) override;

public:
	virtual void SetMovement(bool bHasToMove) override;
};
