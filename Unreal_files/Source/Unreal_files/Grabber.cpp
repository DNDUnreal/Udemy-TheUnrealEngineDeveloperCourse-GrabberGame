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
	FindPhysicsHandleComponent();
	FindBindInputComponent();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ph && ph->GetGrabbedComponent()) ph->SetTargetLocation(endSearching());
}

void UGrabber::Grab() {

	auto hitresult = GetFirstPhisicsBodyInReach();
	auto comptograb = hitresult.GetComponent();
	auto actorHit = hitresult.GetActor();

	if (actorHit && ph) {
		ph->GrabComponent(
			comptograb,
			NAME_None,
			actorHit->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release() {

	if (ph) ph->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent() {

	ph = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (ph == nullptr) UE_LOG(LogTemp, Warning, TEXT("%s lost UPhysicsHandleComponent"), *GetOwner()->GetName());
}

void UGrabber::FindBindInputComponent() {

	in_comp = GetOwner()->FindComponentByClass<UInputComponent>();

	if (in_comp) {
		in_comp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		in_comp->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else UE_LOG(LogTemp, Warning, TEXT("%s lost UInputComponent"), *GetOwner()->GetName());
}

const FHitResult UGrabber::GetFirstPhisicsBodyInReach()
{
	FCollisionQueryParams trace_parm(FName(TEXT("")), false, GetOwner());
	FHitResult out_hit;

	bool hit_result = GetWorld()->LineTraceSingleByObjectType(
		out_hit,
		startSearching(),
		endSearching(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		trace_parm
	);

	return out_hit;
}

const FVector UGrabber::endSearching() {

	FVector out_location;
	FRotator out_rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out_location, out_rotation);

	return out_location + out_rotation.Vector() * ray_scale;
}

const FVector UGrabber::startSearching() {

	FVector out_location;
	FRotator out_rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out_location, out_rotation);

	return out_location;
}

