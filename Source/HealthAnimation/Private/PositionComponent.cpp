// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "PositionComponent.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionComponent::UPositionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionComponent::BeginPlay()
{
	Super::BeginPlay();

	FString name = GetOwner()->GetName();
	FString positionX = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning , TEXT("This is a position of the %s is %s"), + *name, *positionX);
	
}


// Called every frame
void UPositionComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	
}

