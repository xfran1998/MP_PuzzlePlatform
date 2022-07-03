// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "Engine/EngineBaseTypes.h"

#define PRINT(msg) if(GEngine){GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Yellow, msg);}

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformGameInstance()"));
}

void UPuzzlePlatformGameInstance::Init()
{
    Super::Init();
    UE_LOG(LogTemp, Warning, TEXT("Init()"));
}

void UPuzzlePlatformGameInstance::Host()
{
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;

    World->ServerTravel("/Game/Maps/Level1?listen");

    PRINT(FString::Printf(TEXT("Hosting: %s"), *World->GetName()));
}

void UPuzzlePlatformGameInstance::Join(const FString& ServerName)
{
    // UE_LOG(LogTemp, Warning, TEXT("Host: %s"), *ServerName);
    
    PRINT(FString::Printf(TEXT("Joining: %s"), *ServerName));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    PlayerController->ClientTravel(ServerName, ETravelType::TRAVEL_Absolute);
}