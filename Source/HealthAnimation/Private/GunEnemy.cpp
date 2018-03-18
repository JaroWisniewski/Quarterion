// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAnimation.h"
#include "Animation/AnimInstance.h"
#include "GunEnemy.h"
#include "MyProjectile.h"
#include "GameFramework/Pawn.h"

// Sets default values
AGunEnemy::AGunEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
			// Create a gun mesh component

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
		
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	
}

void AGunEnemy::OnFire(FHitResult& Hit)
{
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();

		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position


		const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

		UWorld * const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AMyProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}


	//--------------------------- Calculating Trace Hit and Damage --------------------------------
	// Now send a trace from the end of our gun to see if we should hit anything
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// Calculate the direction of fire and the start location for trace
	FVector CamLoc;
	FRotator CamRot;
	PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector ShootDir = CamRot.Vector();
	ACharacter* Pawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector StartTrace = FVector::ZeroVector;
	if (PlayerController)
	{
		//FRotator UnusedRot;
		//PlayerController->GetPlayerViewPoint(StartTrace, UnusedRot);

		// Adjust trace so there is nothing blocking the ray between the camera and the pawn, and calculate distance from adjusted start
		StartTrace = Pawn->GetActorLocation(); // StartTrace + ShootDir * ((GetActorLocation() - StartTrace) | ShootDir);
	}

	if (WeaponRange==0)
	{
		WeaponRange = 20000;
	}

	// Calculate endpoint of trace
	const FVector EndTrace = StartTrace + ShootDir * WeaponRange;
	
	FCollisionQueryParams TraceParam(FName(TEXT("WeaponTrace")), false, Pawn);
	TraceParam.AddIgnoredActor(this);
	//TraceParam.bTraceAsyncScene = true;
	//TraceParam.bReturnPhysicalMaterial = true;
	FHitResult Impact;

	GetWorld()->LineTraceSingleByObjectType(
		Impact,
		StartTrace,
		EndTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // Collision Channel - have to be set up for PhysicsBody
		TraceParam
	);
	DrawDebugLine(
		GetWorld(),
		StartTrace,
		EndTrace,
		FColor(255, 0, 0),
		false, 31, 0,
		12.333
	);
	// Check for impact
	//const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	Hit = Impact;
	// Deal with impact
	AActor* DamagedActor = Impact.GetActor();
	UPrimitiveComponent* DamagedComponent = Impact.GetComponent();

	if(DamagedActor == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Noooothing"));
	}

	// If we hit an actor, with a component that is simulating physics, apply an impulse
	if ((DamagedActor != NULL) && (DamagedActor != this) && (DamagedComponent != NULL) /*&& DamagedComponent->IsSimulatingPhysics()*/)
	{
	//	DamagedComponent->AddImpulseAtLocation(ShootDir * 100, Impact.Location);
		UE_LOG(LogTemp, Error, TEXT("Hit :: %s"), +*(DamagedActor->GetName()));
		if (DamagedComponent->GetName() == "LeftArm")
		{
			UE_LOG(LogTemp, Error, TEXT("Hit :: LeftArm"));
		}
		else if (DamagedComponent->GetName() == "RightArm")
		{
			UE_LOG(LogTemp, Error, TEXT("Hit :: RightArm"));
		}
		else if (DamagedComponent->GetName() == "RightLeg")
		{
			UE_LOG(LogTemp, Error, TEXT("Hit :: RightLeg"));
		}
		else if (DamagedComponent->GetName() == "LeftLeg")
		{
			UE_LOG(LogTemp, Error, TEXT("Hit :: LeftLeg"));

		}

	}
}

// Called when the game starts or when spawned
void AGunEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

