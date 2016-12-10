// Fill out your copyright notice in the Description page of Project Settings.
#include "LD37_OneRoom.h"
#include "LD37_OneRoomGameMode.h"
#include "Room.h"
#include "Log.h"
#include "FirstPersonPlayer.h"
#include "GoalButtonPanel.h"

const int AOneRoomGameMode::s_cROOM_COUNT = 3;

AOneRoomGameMode::AOneRoomGameMode( const FObjectInitializer& foi )
{
	//PlayerControllerClass = 
	DefaultPawnClass = AFirstPersonPlayer::StaticClass();
}

AOneRoomGameMode::~AOneRoomGameMode( void )
{

}

void AOneRoomGameMode::InitialiseQueue( void )
{
	Room rooms[s_cROOM_COUNT];
	rooms[0].startPoint = 	FVector( 0.0f, 0.0f, 0.0f );
	rooms[0].orientation = 	FRotator( 0.0f, 0.0f, 0.0f );
	rooms[0].endPoint = 	FVector( 0.0f, 5.0f, 0.0f );
	rooms[0].scale = 		FVector( 10.0f, 10.0f, 5.0f );
	rooms[0].timeLimit = 	12.0f;

	rooms[1].startPoint = 	FVector( -18.0f, -18.0f, 0.0f );
	rooms[1].orientation = 	FRotator( 0.0f, 0.0f, 0.0f );
	rooms[1].endPoint = 	FVector( 18.0f, 18.0f, 0.0f );
	rooms[1].scale = 		FVector( 20.0f, 20.0f, 5.0f );
	rooms[1].timeLimit = 	12.0f;

	rooms[2].startPoint = 	FVector( 0.0f, 0.0f, 0.0f );
	rooms[2].orientation = 	FRotator( 0.0f, 0.0f, 0.0f );
	rooms[2].endPoint = 	FVector( 0.0f, 5.0f, 0.0f );
	rooms[2].scale = 		FVector( 10.0f, 10.0f, 5.0f );
	rooms[2].timeLimit = 	20.0f;

	for ( unsigned int i = 0; i < s_cROOM_COUNT; ++i )
	{
		m_rooms.push( rooms[i] );
	}
}

void AOneRoomGameMode::GenerateRoom( void )
{
	Room& nextRoom = m_rooms.front();
	m_pRoomObj->InitRoom( nextRoom );
	m_timeLimit = nextRoom.timeLimit;

	m_rooms.pop();
}

void AOneRoomGameMode::InitRoom( void )
{
	//FActorSpawnParameters spawnDesc;
	//m_pRoomObj = GetWorld()->SpawnActor<ARoom>( ARoom::StaticClass(), spawnDesc );
	
	for ( TActorIterator<ARoom> ActorItr( GetWorld() ); ActorItr; ++ActorItr )
	{
		m_pRoomObj = *ActorItr;
	}

	for( TActorIterator<AGoalButtonPanel> ActorItr( GetWorld() ); ActorItr; ++ActorItr )
	{
		m_pGoal = *ActorItr;
	}

	for( TActorIterator<AFirstPersonPlayer> ActorItr( GetWorld() ); ActorItr; ++ActorItr )
	{
		m_pPlayer = *ActorItr;
		m_pPlayer->SetGoal( m_pGoal );
	}

	if ( !m_pPlayer || !m_pGoal || !m_pRoomObj )
	{
		Log::LogStr( "Error: Missing object player, goal, or room in scene" );
	}

	if ( m_pRoomObj )
	{
		GenerateRoom();
	}
}

void AOneRoomGameMode::StartPlay()
{
	Super::StartPlay();
	InitialiseQueue();
	InitRoom();
}