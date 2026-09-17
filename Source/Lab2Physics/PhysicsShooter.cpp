// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsShooter.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UPhysicsShooter::UPhysicsShooter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPhysicsShooter::BeginPlay()
{
	Super::BeginPlay();

	// This took a little while for me to understand, but basically this is 
	// a convoluted way to get a reference for the controller script for the player
	AActor* Owner = GetOwner();
	if (Owner)
	{
		APawn* OwningPawn = Cast<APawn>(Owner);
		if (OwningPawn)
		{
			OwnerController = OwningPawn->GetController();
		}
	}
}


// Called every frame
void UPhysicsShooter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// This function contains the full physics ray implementation including the 
// ray trace from the camera and the impulse adding. These should probably be separated
// into object detection and physics application, but I didn't bother. 
void UPhysicsShooter::ShootRay()
{
	// Debug to know you're shooting
	UE_LOG(LogTemp, Display, TEXT("Shoot!"));

	// Getting the exact transform of the player camera
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	// Setting the end location of our ray to the vector pointing from the 
	// camera times a variable accessible in the editor.
	FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

	// Create the raycast and hitresult
	FHitResult HitResult;
	/// This parameter array is the type of objects we want to detect (physics bodies)
	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	/// These parameter array is the type of objects we want to ignore (ourselves)
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	/// Finally, calculate the ray as a boolean for if we hit or not
	bool IsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, ViewPointLocation, EndLocation, ObjParams, Params);
	
	if (IsHit)
	{
		// Draw a line indicating the ray and log that we scored a hit.
		DrawDebugLine(GetWorld(), ViewPointLocation, EndLocation, FColor::Red, false, 3.0f);
		UE_LOG(LogTemp, Display, TEXT("HIT!"));

		// Get the specific component that was struck
		UPrimitiveComponent* HitComp = HitResult.GetComponent();

		// Double check that the component exists and is simulating physics
		if (HitComp && HitComp->IsSimulatingPhysics())
		{
			// Calculate the direction of the shot (from start to hit point)
			FVector ShotDirection = (EndLocation - ViewPointLocation).GetSafeNormal();

			// Define the strength of your impulse
			FVector ImpulseVector = ShotDirection * ImpulseStrength;

			// Apply the impulse. Passing HitResult.BoneName ensures it works perfectly on skeletal ragdolls too.
			HitComp->AddImpulse(ImpulseVector, HitResult.BoneName, VelChange);
		}
	}
}

