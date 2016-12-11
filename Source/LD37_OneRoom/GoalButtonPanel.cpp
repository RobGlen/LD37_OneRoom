// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "GoalButtonPanel.h"
#include "Room.h"
#include "LD37_OneRoomGameMode.h"
#include "Log.h"

// Sets default values
AGoalButtonPanel::AGoalButtonPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGoalButtonPanel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalButtonPanel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	LerpLocation( DeltaTime );
}

