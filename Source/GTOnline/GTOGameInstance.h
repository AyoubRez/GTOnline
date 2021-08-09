// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include  "MenuSystem/MenuInterface.h"

#include "GTOGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GTONLINE_API UGTOGameInstance : public UGameInstance, public  IMenuInterface
{
	GENERATED_BODY()

public:
	//Game instance contructor
	UGTOGameInstance(const FObjectInitializer& ObjectInitializer);

	//Game instance init 
	virtual void Init() override;

	//Load Menu function Call 
    UFUNCTION(BlueprintCallable)
	void LoadMenu();

	//Hosting Game function call 
	UFUNCTION(Exec)
	void Host();

	//Joining Game function call 
	UFUNCTION(Exec)
	void Join(const FString& Address );

	
private:

	//Create Menu class to link to Menu BluePrint
	TSubclassOf<class UUserWidget> MenuClass;

	class UMainMenu* Menu;
};
