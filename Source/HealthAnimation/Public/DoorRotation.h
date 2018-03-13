// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorRotation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorOpen);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEALTHANIMATION_API UDoorRotation : public UActorComponent
{
	GENERATED_BODY()

public:	


	//TriggerVolume used to open the door 
	UPROPERTY(EditAnywhere)
	ATriggerVolume * TriggerPlate = nullptr;
	// Time in seconds to close the door
	UPROPERTY(EditAnywhere)
		float TriggerMass = 40.f;

	UPROPERTY(BlueprintAssignable)
		FDoorOpen OnDoorOpen;
	UPROPERTY(BlueprintAssignable)
		FDoorOpen OnDoorClosed;

	// Total Mass of the objects on the trigger plate
	float TotalMass;

	// Sets default values for this component's properties
	UDoorRotation();

	// Called when the game starts
	virtual void BeginPlay() override;

	float GetOverlappingObjectsMass();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
