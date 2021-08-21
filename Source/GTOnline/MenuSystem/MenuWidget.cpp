// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"


void UMenuWidget::SetMenuInterface(IMenuInterface* VMenuInterface)
{
	this->MenuInterface = VMenuInterface;
}

void UMenuWidget::Setup()
{
	// Add Menu to view port 
	this->AddToViewport();
	
	//Getting Player controller
	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();

	// Ensure PlayerController is not Nullptr 
	if(!ensure(PlayerController != nullptr)) return;
    
	//Initiate an Input Mode Data as FInputModeUIOnly
	FInputModeUIOnly InputModeData;
    
	//Setting the widget to focus ad the Menu widget the function needs an SWidget so we use the Function
	//TakeWidget to convert UUserWidget to  SWidget
	InputModeData.SetWidgetToFocus(this->TakeWidget());
    
	//then we lock Mouse to View port as do not lock 
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    
	// then set inputMode in the player controller
	PlayerController->SetInputMode(InputModeData);
	//show Mouse Cursor 
	PlayerController->bShowMouseCursor=true;
}

void UMenuWidget::Teardown()
{
	// Remove Menu from view port 
	this->RemoveFromViewport();

	
	//Getting Player controller
	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();

	// Ensure PlayerController is not Nullptr 
	if(!ensure(PlayerController != nullptr)) return;
    
	//Initiate an Input Mode Data as FInputModeGameOnly
	FInputModeGameOnly InputModeData;    
	// then set inputMode in the player controller
	PlayerController->SetInputMode(InputModeData);
	//hide Mouse Cursor 
	PlayerController->bShowMouseCursor=false;
}