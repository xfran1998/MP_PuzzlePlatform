// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "Materials/MaterialInstance.h"
#include "PlatformTrigger.generated.h"

UCLASS()
class MP_PUZZLEPLATFORM_API APlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* TriggerBox;

	// Material instance when player overlap
	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInstance* PlatformMaterialOverlap;

	// Material instance when player not overlap
	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInstance* PlatformMaterialNotOverlap;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PlatformMesh;

	UStaticMeshComponent* Mesh;

	TArray<class AActor*> Platforms;

	UPROPERTY(EditAnywhere, Category = "Platform")
	int32 Part = 1;

	UFUNCTION(NetMulticast, Unreliable)
	void ChangeColor(bool bIsOverlapping);

	UFUNCTION(NetMulticast, Unreliable)
	void ChangeMovementPlatform(bool bHasToMove);
};
