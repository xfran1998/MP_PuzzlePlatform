// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize()
{
    if ( !Super::Initialize() ) return false;

    if (!ensure(HostButton != nullptr)) return false;
    if (!ensure(JoinButton != nullptr)) return false;
    
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::Host);
    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::Join);

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
    MenuInterface->Join("192.168.1.50");    
}

void UMainMenu::SetMenuInterface(IMenuInterface* NotShadowingVariableNamedMenuInterface)
{
    this->MenuInterface = NotShadowingVariableNamedMenuInterface;
}

void UMainMenu::SetMenuController(APlayerController* NotShadowingVariableNamedMenuController)
{
    this->PlayerController = NotShadowingVariableNamedMenuController;
}

void UMainMenu::SetUpCursorToMenu()
{
    if (!ensure(PlayerController != nullptr)) return;

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);

    PlayerController->bShowMouseCursor = true;
}

void UMainMenu::SetUpCursorToGame()
{
    if (!ensure(PlayerController != nullptr)) return;

    FInputModeGameOnly InputModeData;

    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
}