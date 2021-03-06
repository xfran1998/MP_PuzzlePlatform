// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/World.h"

bool UMainMenu::Initialize()
{
    if ( !Super::Initialize() ) return false;

    // Check all buttons are valid
    if (!ensure(HostButton != nullptr)) return false;
    if (!ensure(JoinButton != nullptr)) return false;
    if (!ensure(BackButton != nullptr)) return false;
    if (!ensure(PlayButton != nullptr)) return false;
    if (!ensure(ExitButton != nullptr)) return false;
    
    // Play the game buttons
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::Host);
    PlayButton->OnClicked.AddDynamic(this, &UMainMenu::Join);
    ExitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

    // Switch widgets buttons
    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
    BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

    UE_LOG(LogTemp, Warning, TEXT("All bindings done"));
    return true;
}

void UMainMenu::Host()
{
    UE_LOG(LogTemp, Warning, TEXT("Hosting1"));

    if (!ensure(MenuInterface != nullptr)) return;
    MenuInterface->Host();    
}

void UMainMenu::Join()
{
    UE_LOG(LogTemp, Warning, TEXT("Joining1"));

    if (!ensure(MenuInterface != nullptr)) return;
    if (!ensure(IPInput != nullptr)) return;

    const FString& IPInputString = IPInput->GetText().ToString();
    // UE_LOG(LogTemp, Warning, TEXT("IP: %s"), *IPInputString);
    if (IPInputString.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("IP is empty"));
        return;
    }

    MenuInterface->Join(IPInputString);    
}

void UMainMenu::OpenJoinMenu()
{

    UE_LOG(LogTemp, Warning, TEXT("Switch to JoinMenu"));
    if (!ensure(MenuSwitcher != nullptr)) return;
    if (!ensure(IPButtons != nullptr)) return;

    MenuSwitcher->SetActiveWidget(IPButtons);
}

void UMainMenu::OpenMainMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("Switch to MainMenu"));
    if (!ensure(MenuSwitcher != nullptr)) return;
    if (!ensure(MainButtons != nullptr)) return;

    MenuSwitcher->SetActiveWidget(MainButtons);
}

void UMainMenu::SetMenuInterface(IMenuInterface* NotShadowingVariableNamedMenuInterface)
{
    this->MenuInterface = NotShadowingVariableNamedMenuInterface;
}

void UMainMenu::SetUpMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("Trying to show cursor"));
    APlayerController* PlayerController = GetOwningPlayer();
    if (!ensure(PlayerController != nullptr)) return;

    this->AddToViewport();
    this->bIsFocusable = true;

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);

    PlayerController->bShowMouseCursor = true;

    UE_LOG(LogTemp, Warning, TEXT("Mouse cursor is visible"));
}

void UMainMenu::SetUpCursorToGame()
{
    APlayerController* PlayerController = GetOwningPlayer();
    if (!ensure(PlayerController != nullptr)) return;

    FInputModeGameOnly InputModeData;

    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
    UE_LOG(LogTemp, Warning, TEXT("Mouse cursor not visible"));
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);

    SetUpCursorToGame();
}

void UMainMenu::QuitGame()
{
    if (!ensure(MenuInterface != nullptr)) return;
    // Letting GameInstance implementation take care of quitting the game
    // becouse maybe need make some stuff before quitting, like saving the game
    MenuInterface->QuitGame();
}