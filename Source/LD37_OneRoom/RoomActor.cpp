// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "RoomActor.h"
#include "Room.h"
#include "LD37_OneRoomGameMode.h"
#include "Log.h"

// Sets default values
ARoomActor::ARoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_updateLocation = false;
	m_updateScale = false;
	m_currentTransform = { GetActorLocation(), GetActorScale3D() };
	m_targetTransform = m_currentTransform;
	m_lerpSpeed = 2.0f;
}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoomActor::UpdateLocation( FVector location )
{
	m_updateLocation = true;
	m_currentTransform.location = GetActorLocation();
	m_targetTransform.location = location;
}

void ARoomActor::UpdateScale( FVector scale )
{
	m_updateScale = true;
	m_currentTransform.scale = GetActorScale();
	m_targetTransform.scale = scale;
}

// Called every frame
void ARoomActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ARoomActor::LerpLocation( float DeltaTime )
{
	if ( m_updateLocation )
	{
		SetActorLocation( m_currentTransform.location );
		Lerp( m_currentTransform.location, m_targetTransform.location, m_updateLocation, DeltaTime );
	}
}

void ARoomActor::LerpScale( float DeltaTime )
{
	if ( m_updateScale )
	{
		SetActorScale3D( m_currentTransform.scale );
		Lerp( m_currentTransform.scale, m_targetTransform.scale, m_updateScale, DeltaTime );
		//Log::LogStr( "HAPS3" );
	}
}

void ARoomActor::Lerp( FVector& current, FVector& target, bool& update, float DeltaTime )
{
	current = FMath::Lerp( current, target, m_lerpSpeed * DeltaTime );
	
	UE_LOG( DebugLog, Log, TEXT( "current: %f,%f,%f. target: %f,%f,%f." ), current.X, current.Y, current.Z, target.X, target.Y, target.Z );
	if ( ( target - current ).Size() <= 0.2f )
	{
		Log::LogStr( "Lerp successful" );
		update = false;
	}
}