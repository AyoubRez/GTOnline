// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


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

	//Quit ************************ 
	//Insure Quit is not a nullptr
	if(!ensure ( QuitButton != nullptr )) return false;
	//on Button clicked we call join Server function 
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);
	
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

void UMainMenu::Quit()
{
	//Getting Player controller
	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();

	// Ensure PlayerController is not Nullptr 
	if(!ensure(PlayerController != nullptr)) return;
	PlayerController->ConsoleCommand("quit");
    
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

