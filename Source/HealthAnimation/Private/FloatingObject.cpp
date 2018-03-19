// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "FloatingObject.h"


// Sets default values for this component's properties
UFloatingObject::UFloatingObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Owner = GetOwner();


	// ...
}


// Called when the game starts
void UFloatingObject::BeginPlay()
{
	Super::BeginPlay();

	active = true;

}

void UFloatingObject::toggle()
{
	if (active)
	{
		active = false;
	}
	else
	{
		active = true;
	}
}


// Called every frame
void UFloatingObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Pawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector P_Location = Pawn->GetActorLocation();
	FVector O_Location = Owner->GetActorLocation();

	int Max_Radius = 250;

	float s = sin(0.01f);
	float c = cos(0.01f);
	if (active)
	{
		float x_dif = O_Location.X - P_Location.X;
		float y_dif = O_Location.Y - P_Location.Y;

		float xnew = x_dif * c - y_dif * s + P_Location.X;
		float ynew = x_dif * s + y_dif * c + P_Location.Y;

		float radius = FMath::Sqrt(FMath::Pow(xnew - P_Location.X, 2.0f) + FMath::Pow(ynew - P_Location.Y, 2.0f));

		if (radius > Max_Radius)
		{
			if (xnew > P_Location.X)
			{
				xnew -= 1.5f;
				ynew -= 1.5f;
			}
			else
			{
				xnew += 1.5f;
				ynew += 1.5f;
			}
		}
		else if (radius < Max_Radius)
		{
			if (xnew < P_Location.X)
			{
				xnew -= 1.5f;
				ynew -= 1.5f;
			}
			else
			{
				xnew += 1.5f;
				ynew += 1.5f;
			}
		}
		FVector Location = FVector(xnew, ynew, O_Location.Z);
		Owner->SetActorLocation(Location);
	}
	else {}
}

