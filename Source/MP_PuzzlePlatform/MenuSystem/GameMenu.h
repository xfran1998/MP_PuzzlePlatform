// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class MP_PUZZLEPLATFORM_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* NotShadowingVariableNamedMenuInterface);
	void SetUpCursorToGame();	
	void SetUpCursorToWidget();	
	void SetUpMenu();
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);
	void CloseMenu();

protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void Continue();
	
	UFUNCTION()
	void BackToMenu();

	// UFUNCTION()
	// void OpenGameMenu();


private:	
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	IMenuInterface* MenuInterface;
};
