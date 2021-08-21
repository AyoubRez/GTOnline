// Fill out your copyright notice in the Description page of Project Settings.


#include "GTOGameInstance.h"
#include "Blueprint/UserWidget.h"

#include "TriggerPlatform.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"


//Game instance Constructor
UGTOGameInstance::UGTOGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// getting hold of trigger platform BP  class 
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/_Game/MenuSystem/WBP_MainMenu"));

	//Ensure MenuBPClass is not nullptr 
	if(!ensure(MenuBPClass.Class!=nullptr)) return;

	//Set MenuClass to MenuBPClass that we got from ContructorHelpers FindClass function 
	MenuClass = MenuBPClass.Class;
	
	// getting hold of trigger platform BP  class 
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/_Game/MenuSystem/WBP_InGameMenu"));

	//Ensure MenuBPClass is not nullptr 
	if(!ensure(InGameMenuBPClass.Class!=nullptr)) return;

	//Set MenuClass to MenuBPClass that we got from Contructor Helpers FindClass function 
	InGameMenuClass = InGameMenuBPClass.Class;
}

//Game instance init function implementation 
void UGTOGameInstance::Init()
{
	UE_LOG(LogTemp,Warning,TEXT("Found Class %s"), *MenuClass->GetName());
}

void UGTOGameInstance::LoadMenu()
{
	//Ensure MenuClass is not a nullptr
	if(!ensure(MenuClass!=nullptr)) return;

	// Create UuserWidget Menu from MenuClass 
    Menu = CreateWidget<UMainMenu>(this,MenuClass);
	
	//Ensure Menu is not nullptr
	if(!ensure(Menu!=nullptr)) return;
	Menu->Setup();
	Menu->SetMenuInterface(this);
	
}

void UGTOGameInstance::InGameLoadMenu()
{
	//Ensure MenuClass is not a nullptr
	if(!ensure(InGameMenuClass!=nullptr)) return;

	// Create UuserWidget Menu from MenuClass 
	UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this,InGameMenuClass);
	
	//Ensure Menu is not nullptr
	if(!ensure(InGameMenu!=nullptr)) return;
	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

// Hosting Game Function implementation 
void UGTOGameInstance::Host()
{
	if(Menu!=nullptr)
	{
		Menu->Teardown();
	}
	// Getting Engine 
	UEngine* Engine = GetEngine();

	// Ensure Engine is not Nullptr 
	if(!ensure(Engine != nullptr)) return;

	//Add Message on screen for debug purposes 
	Engine->AddOnScreenDebugMessage(0,2,FColor::Green, TEXT("Hosting"));

	//Server Travel Implementation
	UWorld* World = GetWorld();
	//Ensure World is not Nullptr
	if(!ensure(World != nullptr)) return;

	//Server Travel to Map as a listen as a server for incoming connections
	World->ServerTravel("/Game/_Game/assets/Maps/ThirdPersonExampleMap?listen");
}

//Join Game Function implementation 
void UGTOGameInstance::Join(const FString& Address)
{
	if(Menu!=nullptr)
	{
		Menu->Teardown();
	}
	//Getting engine 
	UEngine* Engine = GetEngine();

	//Ensure engine is not Nullptr 
	if(!ensure(Engine != nullptr)) return;


	//Add debug Message in screen 
	Engine->AddOnScreenDebugMessage(0,2,FColor::Red,  FString::Printf(TEXT("Joining %s"),*Address));

	//Client travel 
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	// Ensure PlayerController is not Nullptr 
	if(!ensure(PlayerController != nullptr)) return;

	//Client Travel to address as Absolute travel type 
	PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
}

void UGTOGameInstance::LoadMainMenu()
{
	//Client travel 
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	// Ensure PlayerController is not Nullptr 
	if(!ensure(PlayerController != nullptr)) return;

	//Client Travel to address as Absolute travel type 
	PlayerController->ClientTravel("/Game/_Game/assets/Maps/MainMenu",ETravelType::TRAVEL_Absolute);
}
