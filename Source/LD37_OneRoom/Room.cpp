// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "Room.h"
#include "LD37_OneRoomGameMode.h"
#include "Log.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_updateScale = false;
	m_currentScale = GetActorScale3D();
	m_scaleTarget = GetActorScale3D();
	m_lerpSpeed = 2.0f;
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

	if ( m_updateScale )
	{
		SetActorScale3D( m_currentScale );
		m_currentScale = FMath::Lerp( m_currentScale, m_scaleTarget, m_lerpSpeed * DeltaTime );
		
		if ( ( m_scaleTarget - m_currentScale ).Size() <= 0.2f )
		{
			Log::LogStr( "Lerp successful" );
			m_updateScale = false;
		}
	}
}

void ARoom::InitRoom( const Room& roomDesc )
{
	m_currentScale = GetActorScale3D();
	m_scaleTarget = roomDesc.scale;
	m_updateScale = true;
}