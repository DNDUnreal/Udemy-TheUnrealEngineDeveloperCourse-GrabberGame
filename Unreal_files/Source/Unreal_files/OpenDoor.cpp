// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


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

	if (trigger_obj) {
			if (objectmass() > 40) {
				OnOpen.Broadcast();
			}
			else {
				OnClose.Broadcast();
			}
	}
}


float UOpenDoor::objectmass() {

	float totalmass = 0.0f;

	TArray<AActor*> over_geos;
	trigger_obj->GetOverlappingActors(over_geos);

	for (auto& x : over_geos) {
		totalmass += x->FindComponentByClass<UPrimitiveComponent>()->GetMass();

	}
	
	return totalmass;
}