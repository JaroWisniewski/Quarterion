// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunEnemy.generated.h"

UCLASS()
class HEALTHANIMATION_API AGunEnemy : public AActor
{
	GENERATED_BODY()
	
			/** Gun mesh: 1st person view (seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		 class USkeletalMeshComponent* FP_Gun;

			/** Location on gun mesh where projectiles should spawn. */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		 class USceneComponent* FP_MuzzleLocation;

public:	
	// Sets default values for this actor's properties
	AGunEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Fires a virtual projectile. */
	void OnFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimInstance* AnimInstance;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UAnimMontage* FireAnimation;

};
