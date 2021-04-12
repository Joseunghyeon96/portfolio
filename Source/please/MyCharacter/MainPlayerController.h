// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVisibleInventory, bool , _IsVisible);
/**
 * 
 */

UCLASS()
class PLEASE_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Reference to the UMG assaet in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	// Variable to hold the widget after creating it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> WPauseMenu;

	// Variable to hold the widget after creating it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> WPressFText;

	// Variable to hold the widget after creating it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* PressFText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> WItemBox;

	// Variable to hold the widget after creating it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* ItemBox;

	// Variable to hold the widget after creating it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> WHelpMessage;

	// Variable to hold the widget after creating it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* HelpMessage;

	bool bPauseMenuVisible;
	bool bOpenItemBox;
	bool bInvetoryVisible;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "HUD")
	void DisplayPauseMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void RemovePauseMenu();
	bool TogglePauseMenu();

	void DisplayPressF();
	void RemovePressF();

	void DisplayItemBox();
	void RemoveItemBox();

	void DisplayInventory();
	void RemoveInventory();

	void DisplayHelpMessage();
	void RemoveHelpMessage();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FVisibleInventory DelOpenInventory;
};






