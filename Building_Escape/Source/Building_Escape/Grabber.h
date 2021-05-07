// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FindingPhysicsHandleComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector GetLineTraceStart();
private:
	float Reach = 100.0f;
	///for saving the pointer of the shift key pressed
	UInputComponent* InputComponent = nullptr;
	///for saving the pointer of the physics body which the is now connected to
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	void Grab();
	void Release();
	void GettingPhysicsHandleComponent();
	void SetupInputComponent();
	FVector GetLineTraceEnd();
	FVector GetLineTraceBegin();
	const FHitResult GetFirstPhysicsBodyInReach();
};
