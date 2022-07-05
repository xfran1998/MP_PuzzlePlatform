// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"

#include "Engine/Engine.h"
#include "Engine/EngineBaseTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/MainMenu.h"
#include "MovingPlatform.h"

#define PRINT(msg) if(GEngine){GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Yellow, msg);}

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UMainMenu> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
    if (!ensure(MenuBPClass.Class != nullptr)) return;

    MenuClass = MenuBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
    Super::Init();
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
    if (!ensure(MenuClass != nullptr)) return;

    MainMenu = CreateWidget<UMainMenu>(this, MenuClass);
    if (!ensure(MainMenu != nullptr)) return;


    MainMenu->AddToViewport();
    MainMenu->bIsFocusable = true;
    

    MainMenu->SetMenuInterface(this);
    MainMenu->SetMenuController(GetFirstLocalPlayerController());
    MainMenu->SetUpCursorToMenu();
}

void UPuzzlePlatformGameInstance::Host()
{
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;

    World->ServerTravel("/Game/Maps/Level1?listen");

    MainMenu->SetUpCursorToGame();
    PRINT(FString::Printf(TEXT("Hosting: %s"), *World->GetName()));
}

void UPuzzlePlatformGameInstance::Join(const FString& ServerName)
{
    PRINT(FString::Printf(TEXT("Joining: %s"), *ServerName));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    PlayerController->ClientTravel(ServerName, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::Name()
{
    // UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *MenuBPClass.Class->GetName());
}