// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MP_PUZZLEPLATFORM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* NotShadowingVariableNamedMenuInterface);
	void SetMenuController(APlayerController* PlayerController);
	void SetUpCursorToMenu();
	void SetUpCursorToGame();	

protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void Host();
	
	UFUNCTION()
	void Join();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	IMenuInterface* MenuInterface;
	APlayerController* PlayerController;
};
