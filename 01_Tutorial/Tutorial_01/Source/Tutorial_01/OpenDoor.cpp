// Fill out your copyright notice in the Description page of Project Settings.
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();


}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassofTotalObjects() > Massfortrigger) {
		OnOpen.Broadcast();
	}
	else {
		OnClose.Broadcast();
	}
	

}

float UOpenDoor::GetMassofTotalObjects() {
	float TotalMass = 0.f;
	
	TArray<AActor*> Overlappingactors;
	PressurePlate->GetOverlappingActors(OUT Overlappingactors);
	for (auto &actors : Overlappingactors) {
		TotalMass += actors->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("The actor %s has a mass of : %f"), *actors->GetName(), actors->FindComponentByClass<UPrimitiveComponent>()->GetMass());
	}
	
	return TotalMass; 
}

