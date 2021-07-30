// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class GTONLINE_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

	//Public section ***********************************************
public:
	
	//Moving Platform Contructor
	AMovingPlatform();

	virtual void BeginPlay() override;

	//Speed Variable to define the moving speed of the platform
	UPROPERTY(EditAnywhere)
	float Speed = 20.f;

	//Setting Target Location UProperty

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true) )
	FVector TargetLocation;

private:
	 FVector GlobalTargetLocation;
	 FVector GlobalStartLocation;

	
	// Protected Section ********************************************
protected:

	//Tick Event Override 
	virtual void Tick(float DeltaTime) override;
};
