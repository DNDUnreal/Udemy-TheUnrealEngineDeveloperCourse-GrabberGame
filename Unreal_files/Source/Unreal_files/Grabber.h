// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Math/Color.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_FILES_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float ray_scale = 1;
	UPhysicsHandleComponent* ph = nullptr;
	UInputComponent* in_comp = nullptr;

	void Grab();
	void Release();
	void FindPhysicsHandleComponent();
	void FindBindInputComponent();
	const FHitResult GetFirstPhisicsBodyInReach();
	const FVector endSearching();
	const FVector startSearching();
};
