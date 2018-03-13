// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorRotation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEALTHANIMATION_API UDoorRotation : public UActorComponent
{
	GENERATED_BODY()

public:	

	//TriggerVolume used to open the door 
	UPROPERTY(EditAnywhere)
	ATriggerVolume * TriggerPlate = nullptr;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 30.f;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClosedRequest;

	// Total Mass of the objects on the trigger plate
	float TotalMass;

	AActor* Pawn = nullptr;

	// Sets default values for this component's properties
	UDoorRotation();

	// Called when the game starts
	virtual void BeginPlay() override;

	float GetOverlappingObjectsMass();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
