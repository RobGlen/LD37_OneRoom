// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Room.generated.h"

struct Room;

UCLASS()
class LD37_ONEROOM_API ARoom : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ARoom();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void InitRoom( const Room& roomDesc );
};
