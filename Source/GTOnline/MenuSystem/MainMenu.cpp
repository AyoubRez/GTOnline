// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

void UMainMenu::SetMenuInterface(IMenuInterface* VMenuInterface)
{
	this->MenuInterface = VMenuInterface;
}

void UMainMenu::Setup()
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

void UMainMenu::Teardown()
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

bool UMainMenu::Initialize()
{
	//Run Parent class If Initialize returned false then we return false 
	bool Success = Super::Initialize();
	if(!Success) return false;

	//Host ************************ 
	//Insure Host is not a nullptr
	if(!ensure ( HostButton != nullptr )) return false;
	//on Button clicked we call host Server function 
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	//Join ************************ 
	//Insure Join is not a nullptr
	if(!ensure ( JoinButton != nullptr )) return false;
	//on Button clicked we call join Server function 
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	//Back Button ************************ 
	//Insure Join is not a nullptr
	if(!ensure ( CancelJoinMenuButton != nullptr )) return false;
	//on Button clicked we call join Server function 
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	//Join Game Button  ************************ 
	//Insure Join is not a nullptr
	if(!ensure ( ConfirmJoinMenuButton != nullptr )) return false;
	//on Button clicked we call join Server function 
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	//And then we return true 
	return true;
	
}

void UMainMenu::HostServer()
{
	if(MenuInterface!= nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if(MenuInterface!= nullptr)
	{
		if(!ensure(IPAddressField!=nullptr)) return;
		const FString& Address=IPAddressField->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenu::OpenJoinMenu()
{
	//Ensure MenuSwitcher is not a nullptr
	if(!ensure(MenuSwitcher!=nullptr)) return;

	//Ensure JoinMenu is not a nullptr
	if(!ensure(JoinMenu!=nullptr)) return;
	
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	//Ensure MenuSwitcher is not a nullptr
	if(!ensure(MenuSwitcher!=nullptr)) return;

	//Ensure JoinMenu is not a nullptr
	if(!ensure(MainMenu!=nullptr)) return;
	
	MenuSwitcher->SetActiveWidget(MainMenu);
}

