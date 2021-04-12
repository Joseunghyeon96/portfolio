// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "../Enemy.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!HUDOverlayAsset) return;

	HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset, TEXT("HUDOverlay"));
	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	if (WPauseMenu)
	{
		PauseMenu = CreateWidget<UUserWidget>(this, WPauseMenu);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WPressFText)
	{
		PressFText = CreateWidget<UUserWidget>(this, WPressFText);
		if (PressFText)
		{
			PressFText->AddToViewport();
			PressFText->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WItemBox)
	{
		ItemBox = CreateWidget<UUserWidget>(this, WItemBox);
		if (ItemBox)
		{
			ItemBox->AddToViewport();
			ItemBox->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
	if (WHelpMessage)
	{
		HelpMessage = CreateWidget<UUserWidget>(this, WHelpMessage);
		if (HelpMessage)
		{
			HelpMessage->AddToViewport();
			HelpMessage->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPlayerController::DisplayPauseMenu_Implementation()
{
	if (PauseMenu)
	{
		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
		

		FInputModeGameAndUI inputModeGameAndUI;
		SetInputMode(inputModeGameAndUI);
		bShowMouseCursor = true;
	}
}

void AMainPlayerController::RemovePauseMenu_Implementation()
{
	if (PauseMenu)
	{
		FInputModeGameOnly inputModeGameOnly;

		SetInputMode(inputModeGameOnly);
		bShowMouseCursor = false;


		bPauseMenuVisible = false;
	}
}

bool AMainPlayerController::TogglePauseMenu()
{
	if (bPauseMenuVisible)
	{
		RemovePauseMenu();
		return false;
	}
	else
	{
		DisplayPauseMenu();
		return true;
	}
}

void AMainPlayerController::DisplayPressF()
{
	if (PressFText)
	{
		PressFText->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainPlayerController::RemovePressF()
{
	if (PressFText)
	{
		PressFText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainPlayerController::DisplayItemBox()
{
	if (ItemBox)
	{
		ItemBox->SetVisibility(ESlateVisibility::Visible);

		FInputModeGameAndUI inputModeGameAndUI;
		bOpenItemBox = true;
		bShowMouseCursor = true;
		SetInputMode(inputModeGameAndUI);
	}
}

void AMainPlayerController::RemoveItemBox()
{
	if (ItemBox)
	{
		ItemBox->SetVisibility(ESlateVisibility::Hidden);
		FInputModeGameOnly inputModeGameOnly;
		bOpenItemBox = false;
		bShowMouseCursor = false;
		SetInputMode(inputModeGameOnly);
	}
}

void AMainPlayerController::DisplayInventory()
{
		FInputModeGameAndUI inputModeGameAndUI;
		bInvetoryVisible = true;
		bShowMouseCursor = true;
		//bEnableClickEvents = true;
		//bEnableMouseOverEvents = true;
		SetInputMode(inputModeGameAndUI);

		DelOpenInventory.Broadcast(bInvetoryVisible);
}

void AMainPlayerController::RemoveInventory()
{
		FInputModeGameOnly inputModeGameOnly;
		bInvetoryVisible = false;
		bShowMouseCursor = false;
		//bEnableClickEvents = false;
		//bEnableMouseOverEvents = false;
		SetInputMode(inputModeGameOnly);

		DelOpenInventory.Broadcast(bInvetoryVisible);
}

void AMainPlayerController::DisplayHelpMessage()
{
	if (HelpMessage)
	{
		HelpMessage->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainPlayerController::RemoveHelpMessage()
{
	if (HelpMessage)
	{
		HelpMessage->SetVisibility(ESlateVisibility::Hidden);
	}
}




