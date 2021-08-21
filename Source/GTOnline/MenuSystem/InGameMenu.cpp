// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	//Run Parent class If Initialize returned false then we return false 
	bool Success = Super::Initialize();
	if(!Success) return false;

	//Host ************************ 
	//Insure Host is not a nullptr
	if(!ensure ( CancelButton != nullptr )) return false;
	//on Button clicked we call host Server function 
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);

	//Host ************************ 
	//Insure Host is not a nullptr
	if(!ensure ( QuitButton != nullptr )) return false;
	//on Button clicked we call host Server function 
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);
	//And then we return true 
	return true;
	
}

void UInGameMenu::CancelPressed()
{
	Teardown();
}

void UInGameMenu::QuitPressed()
{
	if(MenuInterface != nullptr)
	{
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}

