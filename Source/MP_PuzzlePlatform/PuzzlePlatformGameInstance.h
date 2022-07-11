// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"
 

UCLASS()
class MP_PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer);
	
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadGameMenu();

	UFUNCTION(BlueprintCallable)
	void CloseGameMenu();

	UFUNCTION()
	virtual void Host() override;

	UFUNCTION()
	virtual void Join(const FString& ServerName) override;

	UFUNCTION()
	virtual void OpenMainMenu() override;

	UFUNCTION(Exec)
	void Name();

	UFUNCTION(Exec)
	void OpenGameMenu();

private:
	class TSubclassOf<UUserWidget> MenuClass;
	class TSubclassOf<UUserWidget> GameMenuClass;
	class UMainMenu* MainMenu;
	class UGameMenu* GameMenu;
};
