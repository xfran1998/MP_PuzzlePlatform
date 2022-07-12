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
	void SetUpMenu();
	void SetUpCursorToGame();	
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void Host();
	
	UFUNCTION()
	void Join();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitGame();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainButtons;

	UPROPERTY(meta = (BindWidget))
	class UWidget* IPButtons;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPInput;

	IMenuInterface* MenuInterface;
};
