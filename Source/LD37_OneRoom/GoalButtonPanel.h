// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoomActor.h"

#include "GoalButtonPanel.generated.h"

UCLASS()
class LD37_ONEROOM_API AGoalButtonPanel : public ARoomActor
{
	GENERATED_BODY()
private:
	

public:	
	// Sets default values for this actor's properties
	AGoalButtonPanel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
