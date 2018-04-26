// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"


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

	///Look for attached Physic Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	VerifyInputComponent();
	VerifyPhysicsHandle();
	
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab is pressed"));
	auto HitResult = GetFirstHitReach(); 
	auto GrabedComponent = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if(ActorHit)
	PhysicsHandle->GrabComponent(GrabedComponent, NAME_None, GrabedComponent->GetOwner()->GetActorLocation(), true);
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab is Released"));
	PhysicsHandle->ReleaseComponent();
}

///Input Component verification
void UGrabber::VerifyInputComponent()
{
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s is missing that specific component"), *GetOwner()->GetName());
	}

}

///Physics Handle Component
void UGrabber::VerifyPhysicsHandle()
{
	
	if (PhysicsHandle) {
		return;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s is missing that specific component"), *GetOwner()->GetName());
	}
}

FTwoVectors UGrabber::GetTraceEnd()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;

	// Gets the player ViewPoint (Location, Rotation)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	UE_LOG(LogTemp, Warning, TEXT("Location : %s , Roatation : %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());

	FVector TraceEnd = PlayerLocation + PlayerRotation.Vector()*100.f;
	return FTwoVectors(PlayerLocation, TraceEnd);
}

const FHitResult UGrabber::GetFirstHitReach()
{
	FHitResult Linetracehit;

	GetWorld()->LineTraceSingleByObjectType(OUT Linetracehit, GetTraceEnd().v1, GetTraceEnd().v2, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));

	AActor *FoundActor = Linetracehit.GetActor();

	if (FoundActor != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("You're tracing this object : %s"), *FoundActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing found"));
	}

	return Linetracehit;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent) 
		PhysicsHandle->SetTargetLocation(GetTraceEnd().v2);
}

