// Fill out your copyright notice in the Description page of Project Settings.


#include "GTOGameInstance.h"
#include "Blueprint/UserWidget.h"

#include "TriggerPlatform.h"

UGTOGameInstance::UGTOGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// getting hold of trigger platform BP  class 
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/_Game/MenuSystem/WBP_MainMenu"));

	//Ensure MenuBPClass is not nullptr 
	if(!ensure(MenuBPClass.Class!=nullptr)) return;

	//Set MenuClass to MenuBPClass that we got from ContructorHelpers FindClass function 
	MenuClass = MenuBPClass.Class;
}

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
	if(!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/_Game/assets/Maps/ThirdPersonExampleMap?listen");
}

void UGTOGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();

	if(!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,2,FColor::Red,  FString::Printf(TEXT("Joining %s"),*Address));

	//Client travel 
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
}
