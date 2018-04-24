// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Each Frame

	FVector PlayerLocation;
	FRotator PlayerRotation;

	// Gets the player ViewPoint (Location, Rotation)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	UE_LOG(LogTemp, Warning, TEXT("Location : %s , Roatation : %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector()*100.f; 

	DrawDebugLine(GetWorld(), PlayerLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 2.f);
	FHitResult Linetracehit;

	GetWorld()->LineTraceSingleByObjectType(OUT Linetracehit, PlayerLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));

	AActor *FoundActor = Linetracehit.GetActor(); 

	if (FoundActor != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("You're tracing this object : %s"), *FoundActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing found"));
	}
}

