// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"

#include "Engine/Engine.h"
#include "Engine/EngineBaseTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"
#include "MovingPlatform.h"

#define PRINT(msg) if(GEngine){GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Yellow, msg);}

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UMainMenu> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
    if (!ensure(MenuBPClass.Class != nullptr)) return;

    MenuClass = MenuBPClass.Class;
    UE_LOG(LogTemp, Warning, TEXT("Menu class getted"));

    ConstructorHelpers::FClassFinder<UGameMenu> GameMenuBPClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));
    if (!ensure(GameMenuBPClass.Class != nullptr)) return;

    GameMenuClass = GameMenuBPClass.Class;
    UE_LOG(LogTemp, Warning, TEXT("Game class getted"));
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
    

    MainMenu->SetMenuInterface(this);
    MainMenu->SetUpMenu();
}

void UPuzzlePlatformGameInstance::LoadGameMenu()
{
    if (!ensure(GameMenuClass != nullptr)) return;

    GameMenu = CreateWidget<UGameMenu>(this, GameMenuClass);
    if (!ensure(GameMenu != nullptr)) return;
    

    GameMenu->SetMenuInterface(this);
    GameMenu->SetUpMenu();
}

void UPuzzlePlatformGameInstance::CloseGameMenu()
{    
    if (!ensure(GameMenu != nullptr)) return;
    GameMenu->CloseMenu();
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
    PRINT(FString::Printf(TEXT("Joining: %s"), *ServerName));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    PlayerController->ClientTravel(ServerName, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::OpenMainMenu()
{
    PRINT(FString::Printf(TEXT("Goin back to Lobby")));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    // Send the player back to the main menu.
    PlayerController->ClientTravel("/Game/Maps/Lobby", ETravelType::TRAVEL_Absolute);

    // LoadMenu();
}

void UPuzzlePlatformGameInstance::Name()
{
    if (!ensure(MenuClass != nullptr)) return;
    UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *MenuClass->GetName());
}

void UPuzzlePlatformGameInstance::OpenGameMenu()
{
    this->LoadGameMenu();
}
