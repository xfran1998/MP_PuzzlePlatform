// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"

#include "Components/Button.h"
#include "Engine/World.h"

bool UGameMenu::Initialize()
{
    if ( !Super::Initialize() ) return false;

    if (!ensure(BackButton != nullptr)) return false;
    if (!ensure(PlayButton != nullptr)) return false;
    
    // Play the game buttons
    PlayButton->OnClicked.AddDynamic(this, &UGameMenu::Continue);
    BackButton->OnClicked.AddDynamic(this, &UGameMenu::BackToMenu);

    UE_LOG(LogTemp, Warning, TEXT("All bindings done"));
    return true;
}

void UGameMenu::Continue()
{
    this->CloseMenu();
}

void UGameMenu::CloseMenu()
{
    // Remove this widget from the viewport
    this->RemoveFromViewport();

    // Cursor to game
    SetUpCursorToGame();
}

void UGameMenu::BackToMenu()
{
    if (!ensure(MenuInterface != nullptr)) return;
    MenuInterface->OpenMainMenu();
}

// void UGameMenu::OpenGameMenu()
// {
//     UE_LOG(LogTemp, Warning, TEXT("Switch to MainMenu"));
//     if (!ensure(MenuSwitcher != nullptr)) return;
//     if (!ensure(MainButtons != nullptr)) return;

//     MenuSwitcher->SetActiveWidget(MainButtons);
// }

void UGameMenu::SetMenuInterface(IMenuInterface* NotShadowingVariableNamedMenuInterface)
{
    this->MenuInterface = NotShadowingVariableNamedMenuInterface;
}

void UGameMenu::SetUpMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("Trying to show cursor"));
    this->AddToViewport();
    this->bIsFocusable = true;

    SetUpCursorToWidget();
}

void UGameMenu::SetUpCursorToWidget()
{
    APlayerController* PlayerController = GetOwningPlayer();
    if (!ensure(PlayerController != nullptr)) return;

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);

    PlayerController->bShowMouseCursor = true;

    UE_LOG(LogTemp, Warning, TEXT("Mouse cursor is visible"));
}

void UGameMenu::SetUpCursorToGame()
{
    APlayerController* PlayerController = GetOwningPlayer();
    if (!ensure(PlayerController != nullptr)) return;

    FInputModeGameOnly InputModeData;

    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
    UE_LOG(LogTemp, Warning, TEXT("Mouse cursor not visible"));
}

void UGameMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);

    SetUpCursorToGame();
}