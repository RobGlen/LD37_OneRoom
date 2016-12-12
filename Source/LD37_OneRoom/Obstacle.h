// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoomActor.h"
#include "Obstacle.generated.h"

/**
 * 
 */
UCLASS()
class LD37_ONEROOM_API AObstacle : public ARoomActor
{
	GENERATED_BODY()
	
public:
	AObstacle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	
};
