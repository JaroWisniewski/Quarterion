// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FollowingObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEALTHANIMATION_API UFollowingObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	AActor* Owner;
	ACharacter* Pawn;
	bool active;


	// Sets default values for this component's properties
	UFollowingObject();
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void toggle();
	
};
