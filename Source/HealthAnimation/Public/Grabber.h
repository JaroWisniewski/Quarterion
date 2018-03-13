// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEALTHANIMATION_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Main characters shield on or off
	bool shield;

	// Main Character using the Grabber
	AActor * Pawn = nullptr;

	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	//Array of floating Object
	TArray <AActor*> arrFloatingObjects;

	//Array of components
	TArray <UStaticMeshComponent*> arrComponents;

	// Grabbing Range
	float Reach	= 500.0f;

	//Power of Force
	float ForcePower = 10000.0f;

	// Character Physics Handle
	UPhysicsHandleComponent* PhysxHandle = nullptr;

	// Player Input Controller
	UInputComponent* InputComponent = nullptr;

	//Grab Function
	void Grab();

	//Release Function
	void Release();

	//Get Physics Handle
	void FindPhysicsHandleComponent();

	//Get Input Component
	void SetupInputController();
	
	//Get Characters Reach Line Starting point (Location)
	FVector GetReachLineStart();
	
	//Get Character Reach Line End Point of grab 
	FVector GetReachLineEnd();

	//Line Trace for object
	FHitResult TraceForObject();
};
