// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

//Constructor Implementation ***********************
AMovingPlatform::AMovingPlatform()
{
	//Our Platform Can Tick 
	PrimaryActorTick.bCanEverTick=true;

	//Set Mobility to Movable to avoid Errors while Moving the Platform (Static)
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	//This should be executed ONly on client Side 
	if(HasAuthority())
	{
		//Set replication to Client Side 
        SetReplicates(true);
        	
        //Replicate Movement of Platform 
        SetReplicateMovement(true);
	}

	GlobalStartLocation=GetActorLocation();
	
	//The Target Location a relative but we want the Absolute position in the world 
	GlobalTargetLocation=GetTransform().TransformPosition(TargetLocation);
	
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if(ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}

//Tick Event Implementation ***********************
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(ActiveTriggers>0)
	{
		//If User is the server we should Move the platform otherwise not :
		//The Code is running only on server 
		if(HasAuthority())
		{
		
			//Getting Actor Location 
			FVector Location = GetActorLocation();

			//Getting the lenght of vector between Start and target location 
			float JourneyLenght =  (GlobalTargetLocation-GlobalStartLocation).Size();

			//The lenght of the vector between current location and startLocation 
			float JourneyTraveled = (Location-GlobalStartLocation).Size();


			if(JourneyTraveled >= JourneyLenght)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation=GlobalTargetLocation;
				GlobalTargetLocation=Swap;
			}
		
			/*Getting the Direction where we should move our platform
			* normalizing the direction because function called every tick
			*we want platform to move continuisly until reach target */
		
			FVector Direction = (GlobalTargetLocation-GlobalStartLocation).GetSafeNormal();

			//Set the new Location to the speed multiplied by deltaTime and Direction 
			Location += Speed*DeltaTime*Direction;

			//Setting Actor New Location
			SetActorLocation(Location);
		
		}
	}
}
