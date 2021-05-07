// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	///Beacause we want to use grab on physicalbody only.
	GettingPhysicsHandleComponent();
	///Because we want to grab when a button is pressed.
	SetupInputComponent();
}
///For grabing physical objects which are chair and table by the default pawn i have made
void UGrabber::Grab()
{
	///We get the Object which has been hitted.
	auto HitResult = GetFirstPhysicsBodyInReach();
	///We get the component.
	auto ComponentToGrab = HitResult.GetComponent();
	///We get the actor.
	auto ActorHit = HitResult.GetActor();
	if (ActorHit) {
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true /*allowing rotation*/);
	}
}
///For releasing the object
void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}
///Getting the physical handle characteristics as i needed work with physical body
void UGrabber::GettingPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}
///setting up the input shift because with the use of this button the player can grab and release
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	///For Binding Action.
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	///if the player have grabbed a physical object then
	///it needs to be changing location when the player change its location.
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

///it is the ending point of the distance from which the player can use grab ability
FVector UGrabber::GetLineTraceEnd()
{
	///For saving the player location at the moment
	FVector PlayerViewPointLocation;
	///For saving the player rotation at the moment
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

///it is the starting point of the distance from which the player can use grab ability
FVector UGrabber::GetLineTraceBegin()
{
	///For saving the player location at the moment
	FVector PlayerViewPointLocation;
	///For saving the player rotation at the moment
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///setup query parameters.
	///Third parameter is for the actor we want to ignore. in this case it is the owner.
	///Not doing anything complex. so 2nd parameter is set to false.
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///Line trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetLineTraceBegin(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	return Hit;
}


