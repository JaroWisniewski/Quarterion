// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "DoorRotation.h"


// Sets default values for this component's properties
UDoorRotation::UDoorRotation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UDoorRotation::BeginPlay()
{
	Super::BeginPlay();	

	Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UDoorRotation::OpenDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.0f, 80.0f, 0.0f));
}

void UDoorRotation::CloseDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UDoorRotation::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (TriggerPlate->IsOverlappingActor(Pawn))
	{
		OpenDoor();
		start = GetWorld()->GetTimeSeconds();
	}
	if (start + CloseDelay < GetWorld()->GetTimeSeconds())
	{
		CloseDoor();
	}
	// ...
}
