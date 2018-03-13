// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "FollowingObject.h"
//#include "FirstPersonProjectile.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Assigns Character to Pawn
	Pawn = GetOwner();

	FindPhysicsHandleComponent();

	SetupInputController();

	shield = false;

}

void UGrabber::SetupInputController()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();


	if (InputComponent)
	{
		///Binding Action
		UE_LOG(LogTemp, Warning, TEXT("<<<Binding Input to a Controller - %s>>>"), +*(Pawn->GetName()));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Release", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		///Log unavailable Input Controller
		UE_LOG(LogTemp, Error, TEXT("<<<Input Component not found - %s>>>"), +*(Pawn->GetName()));
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
		
		PhysxHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysxHandle == nullptr)
	{
		//Log unavailable Physics Handler
		UE_LOG(LogTemp, Error, TEXT("<<<Physics Handle not found - %s>>>"), +*(Pawn->GetName()));
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = TraceForObject();
	auto Hit = HitResult.GetComponent();

		if (Hit == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Object selected"));
		}
		else
		{
			AActor* Object = HitResult.GetActor();

			///Rotation experiment
			/*FVector Location;
			FRotator Rotation;
			GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);*/
			// Rotating Object
			UFollowingObject* flObject = nullptr;
			flObject = Object->FindComponentByClass<UFollowingObject>();
			if (flObject)
			{

				UE_LOG(LogTemp, Warning, TEXT("Floating Object "));
				flObject->toggle();
				arrFloatingObjects.AddUnique(Object);
				shield = true;
				//flObject->active = true;
				//PhysxHandle->GrabComponentAtLocationWithRotation(
				//	Hit,
				//	NAME_None,
				//	Hit->GetOwner()->GetActorLocation(),
				//	Hit->GetOwner()->GetActorRotation()
				//);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Simple Object "));
			}
		}
}
	

void UGrabber::Release()
{
	FHitResult HitResult = TraceForObject();
	auto Hit = HitResult.GetComponent();
	if (shield)
	{
		for (AActor* &Str : arrFloatingObjects)
		{
			FVector positionC = Str->GetActorLocation();
			FVector positionA = Pawn->GetActorLocation();
			int x = positionC.X - positionA.X;
			int y = positionC.Y - positionA.Y;
			int z = positionC.Z - positionA.Z;


			FVector Force = FVector (x * ForcePower, y * ForcePower, z);

			Str->GetComponents<UStaticMeshComponent>(arrComponents);

			Str->GetActorLocation();
			UFollowingObject* flObject = Str->FindComponentByClass<UFollowingObject>();
			flObject->toggle();
			arrComponents[0]->AddForce(Force);
		}
		arrComponents.Empty();
		arrFloatingObjects.Empty();
		shield = false;
	}
	else
	{
		FActorSpawnParameters SpawnInfo;
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
//		FActorSpawnParameters SpawnInfo;
//		GetWorld()->SpawnActor<AProjectile>(Location, Rotation, SpawnInfo);
		{
			// Actor has been spawned in the level
		}
	//	else
		{
			// Failed to spawn actor!
		}
		UE_LOG(LogTemp, Warning, TEXT("Shield Off"));
	}
}

FVector UGrabber::GetReachLineStart()
{
	//ViewPoint Location
	FVector Location;
	//ViewPoint Rotation
	FRotator Rotation;

	//Assign Current View values every Tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);

	//Calculate end point of Reach
	return Location;
}

FVector UGrabber::GetReachLineEnd()

{
	//ViewPoint Location
	FVector Location;
	//ViewPoint Rotation
	FRotator Rotation;

	//Assign Current View values every Tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);

	//Calculate end point of Reach
	FVector EndPoint = Location + (Rotation.Vector() * Reach);

	return EndPoint;
}

FHitResult UGrabber::TraceForObject()
{

	//Trace Parameters
	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());

	//Hit Object holding additional Information about the Hit
	FHitResult Hit;

	//TODO - Trace by Sphere 

	//FCollisionShape MySphere = FCollisionShape::MakeSphere(500.0f); // 5M Radius
	//TArray <FHitResult> OutResults;
	//GetWorld()->SweepMultiByObjectType(
	//	OutResults, 
	//	GetReachLineStart(),
	//	GetReachLineEnd(),
	//	FQuat::Identity, 
	//	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // Collision Channel - have to be set up for PhysicsBody,
	//	MySphere,
	//	TraceParam
	//);

	///Tracing Line
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // Collision Channel - have to be set up for PhysicsBody
		TraceParam
	);
	//Aimed Object
	AActor* HitActor = Hit.GetActor();

	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabbed %s"), +*(HitActor->GetName()));
	}

	return Hit;
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

}

