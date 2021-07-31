// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlatform.h"

#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
ATriggerPlatform::ATriggerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Trigger volume
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));


	//Check if trigger volume is not null to not crash editor 
	if(!ensure(TriggerVolume!=nullptr)) return;

	//Assign To Root component
	RootComponent = TriggerVolume;

	//Link Component begin over lap with the onOverlapBegin function 
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this,&ATriggerPlatform::OnOverlapBegin);
	//Link Component end over lap with the onOverlapEnd function 
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this,&ATriggerPlatform::OnOverlapEnd);
	
}

// Called when the game starts or when spawned
void ATriggerPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATriggerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//on begin over lap increment Active trigger for all Platforms To Trigger
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void ATriggerPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//on End over lap decrement  Active trigger for all Platforms To Trigger
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}

