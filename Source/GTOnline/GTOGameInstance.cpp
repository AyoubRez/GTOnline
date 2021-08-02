// Fill out your copyright notice in the Description page of Project Settings.


#include "GTOGameInstance.h"
#include "Blueprint/UserWidget.h"

#include "TriggerPlatform.h"

//Game instance Constructor
UGTOGameInstance::UGTOGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// getting hold of trigger platform BP  class 
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/_Game/MenuSystem/WBP_MainMenu"));

	//Ensure MenuBPClass is not nullptr 
	if(!ensure(MenuBPClass.Class!=nullptr)) return;

	//Set MenuClass to MenuBPClass that we got from ContructorHelpers FindClass function 
	MenuClass = MenuBPClass.Class;
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
	UUserWidget* Menu = CreateWidget<UUserWidget>(this,MenuClass);

	//Ensure Menu is not nullptr
	if(!ensure(Menu!=nullptr)) return;

	// Add Menu to view port 
	Menu->AddToViewport();

	//Getting Player controller  
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	// Ensure PlayerController is not Nullptr 
	if(!ensure(PlayerController != nullptr)) return;

	//Initiate an Input Mode Data as FInputModeUIOnly
	FInputModeUIOnly InputeModeData;

	//Setting the widget to focus ad the Menu widget the function needs an SWidget so we use the Function
	//TakeWidget to convert UUserWidget to  SWidget
	InputeModeData.SetWidgetToFocus(Menu->TakeWidget());

	//then we lock Mouse to View port as do not lock 
	InputeModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	// then set inputMode in the player controller 
	PlayerController->SetInputMode(InputeModeData);
	//show Mouse Cursor 
	PlayerController->bShowMouseCursor=true;
	
}

// Hosting Game Function implementation 
void UGTOGameInstance::Host()
{
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
