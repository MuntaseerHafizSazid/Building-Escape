// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CloseDoor();
	///to use bluprint to make the door open with timeline animation.
	UPROPERTY(BlueprintAssignable)
		FOnOpenRequest FOnOpenRequest;
	///to use bluprint to make the door close with timeline animation.
	UPROPERTY(BlueprintAssignable)
		FOnCloseRequest FOnCloseRequest;
private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = -90.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
		float TriggerMass = 0.0f;
	///for saving the the owner as pointer and use it as instance
	AActor* Owner = nullptr;
	float GetTotalMassOfActorsOnPlate();
};
