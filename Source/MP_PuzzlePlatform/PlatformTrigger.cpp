// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"
#include "MovingPlatform.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Components/ChildActorComponent.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a box component
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	if (!ensure(TriggerBox != nullptr))	return; // Ensure that the box component is not null
	TriggerBox->SetCollisionProfileName(TEXT("Trigger")); // Set the collision profile of the box component to be a trigger
	
	// Set the trigger box as a root component
	RootComponent = TriggerBox;

}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		// Set this actor to replicate
		this->SetReplicates(true);

		// Set the trigger box callback
		if (!ensure(TriggerBox != nullptr))	return; // Ensure that the box component is not null
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);

		FString TagName = FString::FromInt(Part);

		// Get all platform actors of Part1
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AMovingPlatform::StaticClass(), FName(*TagName), Platforms);
	}

	// Get the static mesh component child of this actor
	Mesh = this->FindComponentByClass<UStaticMeshComponent>();
	
	// Change the material to not overlap
	ChangeColor(false);
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		// Change the material to overlap
		ChangeColor(true);

		// Change the movement of the platform
		ChangeMovementPlatform(true);
	}
}

void APlatformTrigger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HasAuthority())
	{
		// Change the material to not overlap
		ChangeColor(false);

		// Change the movement of the platform
		ChangeMovementPlatform(false);
	}
}

void APlatformTrigger::ChangeColor_Implementation(bool bIsOverlapping)
{
	// if (HasAuthority()) return;

	if (!ensure(Mesh != nullptr)) return; // Ensure that the mesh component is not null

	// Change the material to not overlap
	if (bIsOverlapping)	
		Mesh->SetMaterial(0, PlatformMaterialOverlap);
	else 
		Mesh-> SetMaterial(0, PlatformMaterialNotOverlap);
}

void APlatformTrigger::ChangeMovementPlatform_Implementation(bool bHasToMove)
{
	// Print the name of platform actors
	for (AActor* Platform : Platforms)
	{

		// Change if platform can move
		AMovingPlatform* MovingPlatform = Cast<AMovingPlatform>(Platform);
		if (MovingPlatform)
			MovingPlatform->SetMovement(bHasToMove);		
	}
}
