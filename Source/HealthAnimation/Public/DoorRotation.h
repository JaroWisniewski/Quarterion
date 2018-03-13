// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorRotation.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEALTHANIMATION_API UDoorRotation : public UActorComponent
{
	GENERATED_BODY()

public:	


	//TriggerVolume used to open the door 
	UPROPERTY(EditAnywhere)
	ATriggerVolume * TriggerPlate;
	// Time in seconds to close the door
	UPROPERTY(EditAnywhere)
		float CloseDelay;
	//Time when player stepped on the Trigger Plate
	float start;
	// Total Mass of the objects on the trigger plate
	float TotalMass;

	AActor* Pawn;

	// Sets default values for this component's properties
	UDoorRotation();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

	float GetOverlappingObjectsMass();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
