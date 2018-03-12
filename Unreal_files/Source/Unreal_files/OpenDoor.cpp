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

	actor[0] = GetWorld()->GetFirstPlayerController()->GetPawn();
	owner = GetOwner();
	owner_rot = owner->GetActorRotation();
	
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (trigger_obj) {
		for (AActor* x : actor) {
			if (trigger_obj->IsOverlappingActor(x)) {
				open_door();
				last_open_time = GetWorld()->GetTimeSeconds();
				break;
			}
		}
	}

	if (GetWorld()->GetTimeSeconds() >= (last_open_time + delay_time)) close_door();
}

void UOpenDoor::open_door()
{
	FRotator open_rot = owner_rot + FRotator(0, open_angle, 0);
	owner->SetActorRotation(open_rot);
}

void UOpenDoor::close_door()
{
	owner->SetActorRelativeRotation(owner_rot);
}

