// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GTOGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GTONLINE_API UGTOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UGTOGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address );
};
