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
	
}

float UDoorRotation::GetOverlappingObjectsMass()
{
	TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	TriggerPlate->GetOverlappingActors(OverlappingActors);
	for (auto* Object : OverlappingActors)
	{
		TotalMass += Object->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Total mass of all the objects is %f"), +TotalMass);
	}
	return TotalMass;
}

// Called every frame
void UDoorRotation::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetOverlappingObjectsMass() > TriggerMass)
	{
		OnDoorOpen.Broadcast();
	}
	else
	{
		OnDoorClosed.Broadcast();
	}
}

