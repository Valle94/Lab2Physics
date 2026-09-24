// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "PhysicsShooter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LAB2PHYSICS_API UPhysicsShooter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhysicsShooter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Set up a reference to the owner controller
	AController* OwnerController;

	// Float for the max range of the ray trace
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float MaxRange = 10000.0f;

	// Float for the impulse strength
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ImpulseStrength = 5000.0f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	bool VelChange = true;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int Ammo = 10;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ReloadTime = 4.0f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ReloadTimer = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	bool CanShoot = true;

	// Create a member variable as a reference to our bullet
	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<AProjectile> ProjectileClass;

	// Function to shoot the physics ray; called using bluebrints. 
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void ShootRay();

	// Function to shoot the physics ray; called using bluebrints. 
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void ShootBullet();

	// Function to shoot the physics ray; called using bluebrints. 
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Reload();
};
