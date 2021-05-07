// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/TriggerVolume.h"
#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Components/PrimitiveComponent.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//OpenDoor();
	Owner = GetOwner();
	// ...
	
}

void UOpenDoor::OpenDoor()
{
	///Owner->SetActorRotation(FRotator(0.0, OpenAngle, 0.0));
	FOnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	///Owner->SetActorRotation(FRotator(0.0, 0.0, 0.0));
	FOnCloseRequest.Broadcast();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
		OpenDoor();
	}
	else 
	{
		CloseDoor();
	}
	// ...
}
///for getting the total mass on the trigger volume
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	///for saving the instance of the actor which are on the trigger volume at the moment
	TArray<AActor*>OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	///getting the actors mass and summing those values
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}


