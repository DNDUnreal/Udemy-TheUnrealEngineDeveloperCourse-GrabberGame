// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Containers/Array.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_FILES_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void open_door();

	void close_door();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor * owner;
	FRotator owner_rot;
	float last_open_time = 0;

	UPROPERTY(EditAnywhere)
	float open_angle = -45.0f;

	UPROPERTY(EditAnywhere)
	float delay_time = 1.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* trigger_obj = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> actor;
	
};
