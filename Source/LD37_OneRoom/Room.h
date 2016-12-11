// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoomActor.h"
#include "Room.generated.h"

struct Room;

UCLASS()
class LD37_ONEROOM_API ARoom : public ARoomActor
{
	GENERATED_BODY()
private:

public:	
	// Sets default values for this actor's properties
	ARoom();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
