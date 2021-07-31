// Fill out your copyright notice in the Description page of Project Settings.


#include "GTOGameInstance.h"

UGTOGameInstance::UGTOGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp,Warning,TEXT("Game instance contructor"));
}

void UGTOGameInstance::Init()
{
	UE_LOG(LogTemp,Warning,TEXT("Game instance init"));
}

void UGTOGameInstance::Host()
{
	UEngine* Engine = GetEngine();

	if(!ensure(Engine != nullptr)) return;

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

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
}
