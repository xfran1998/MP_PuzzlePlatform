// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MP_PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

    virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category="Movement")
	float Speed = 100.f;

	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, Category="Movement", Meta=(MakeEditWidget=true))
	FVector FinalPos;

	float MaxDistance;
	FVector StartPos;
	FVector NormalTravel;

	bool HasArrived() const;
	virtual void MovePlatform(const float &DeltaTime);
	FVector GetNextLocation(const float &DeltaTime) const;
	void ChangeSpeed();
	void ChangeEndPoints();

public:
	virtual void SetMovement(bool bHasToMove);
};
