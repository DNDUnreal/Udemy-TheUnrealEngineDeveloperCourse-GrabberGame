// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


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

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector out_location;
	FRotator out_rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out_location, out_rotation);

	UE_LOG(LogTemp, Warning, TEXT("View at %s, rotations are %s"), *out_location.ToString(), *out_rotation.ToString());

	FVector end_of_LT = out_location + out_rotation.Vector() * ray_scale;

	DrawDebugLine(
		GetWorld(),
		out_location,
		end_of_LT,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10
	);
}

