// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "Room.h"
#include "LD37_OneRoomGameMode.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ARoom::InitRoom( const Room& roomDesc )
{
	FTransform transform;
	transform.SetScale3D( roomDesc.scale );
	SetActorTransform( transform, true );
}