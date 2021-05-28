// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleController.h"
#include "Blueprint/UserWidget.h"

void ATitleController::BeginPlay()
{
	Super::BeginPlay();

	if (UIWidgetClass != nullptr)
	{
		UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
		if (UIWidgetInstance != nullptr)
		{
			UIWidgetInstance->AddToViewport();

			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
			SetInputMode(Mode);
			bShowMouseCursor = true;
		}
	}
}