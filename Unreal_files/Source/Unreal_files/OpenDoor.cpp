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

	owner = GetOwner();
	if(owner) owner_rot = owner->GetActorRotation();
	
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (trigger_obj) {
			if (objectmass() > 40) {
				open_door();
				last_open_time = GetWorld()->GetTimeSeconds();
			}
	}

	if (GetWorld()->GetTimeSeconds() >= (last_open_time + delay_time)) close_door();
}

void UOpenDoor::open_door()
{
	/*FRotator open_rot = owner_rot + FRotator(0, open_angle, 0);
	if(owner) owner->SetActorRotation(open_rot);*/

	OnOpenRequest.Broadcast();
}

void UOpenDoor::close_door()
{
	if(owner) owner->SetActorRelativeRotation(owner_rot);
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