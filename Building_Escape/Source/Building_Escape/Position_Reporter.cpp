// Fill out your copyright notice in the Description page of Project Settings.


#include "Position_Reporter.h"

// Sets default values for this component's properties
UPosition_Reporter::UPosition_Reporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPosition_Reporter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Position reporter reporting"));
	// ...
	
}


// Called every frame
void UPosition_Reporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

