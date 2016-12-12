// Fill out your copyright notice in the Description page of Project Settings.
#include "LD37_OneRoom.h"
#include "LD37_OneRoomGameMode.h"
#include "Room.h"
#include "Log.h"
#include "FirstPersonPlayer.h"
#include "GoalButtonPanel.h"
#include "OneRoomHUD.h"

const int AOneRoomGameMode::s_cROOM_COUNT = 6;

AOneRoomGameMode::AOneRoomGameMode( const FObjectInitializer& foi )
{
	//PlayerControllerClass = 
	DefaultPawnClass = AFirstPersonPlayer::StaticClass();
	HUDClass = AOneRoomHUD::StaticClass();
}

AOneRoomGameMode::~AOneRoomGameMode( void )
{

}

void AOneRoomGameMode::InitialiseQueue( void )
{
	Room rooms[s_cROOM_COUNT];
	rooms[0].startPoint = 	FVector( 0.0f, 0.0f, 0.0f );
	rooms[0].orientation = 	FRotator( 0.0f, 0.0f, 0.0f );
	rooms[0].endPoint = 	FVector( 300.0f, 0.0f, -200.0f );
	rooms[0].scale = 		FVector( 10.0f, 10.0f, 5.0f );
	rooms[0].timeLimit = 	12.0f;

	rooms[1].startPoint = 	FVector( -500.0f, -500.0f, -100.0f );
	rooms[1].orientation = 	FRotator( 0.0f, 0.0f, 0.0f );
	rooms[1].endPoint = 	FVector( 500.0f, 500.0f, -200.0f );
	rooms[1].scale = 		FVector( 20.0f, 20.0f, 5.0f );
	rooms[1].timeLimit = 	12.0f;

	rooms[2].startPoint = 	FVector( 0.0f, 0.0f, 1000.0f );
	rooms[2].orientation = 	FRotator( 0.0f, 0.0f, 0.0f );
	rooms[2].endPoint = 	FVector( 0.0f, 0.0f, -1950.0f );
	rooms[2].scale = 		FVector( 5.0f, 5.0f, 40.0f );
	rooms[2].timeLimit = 	20.0f;

	rooms[3].startPoint = 	FVector( -100.0f, 0.0f, 0.0f );
	rooms[3].orientation = 	FRotator( 0.0f, 0.0f, 0.0f );
	rooms[3].endPoint = 	FVector( 300.0f, 0.0f, -100.0f );
	rooms[3].scale = 		FVector( 40.0f, 40.0f, 5.0f );
	Obstacle ob = { OBJSTACLETYPE_BOX, FVector( 300.0f, 0.0f, -200.0f ), FVector( 2.0f, 2.0f, 1.0f ) };
	rooms[3].obstacles.push_back( ob );
	rooms[3].timeLimit = 	12.0f;

	rooms[0].startPoint = 	FVector( -100.0f, 0.0f, 0.0f );
	rooms[0].orientation = 	FRotator( 0.0f, 0.0f, 0.0f );
	rooms[0].endPoint = 	FVector( 600.0f, 0.0f, -930.0f );
	rooms[0].scale = 		FVector( 60.0f, 60.0f, 20.0f );
	Obstacle ob1 = { OBJSTACLETYPE_BOX, FVector( 600.0f, 0.0f, -960.0f ), FVector( 2.0f, 2.0f, 2.0f ) };
	Obstacle ob2 = { OBJSTACLETYPE_BOX, FVector( 300.0f, 0.0f, -960.0f ), FVector( 8.0f, 8.0f, 1.0f ) };
	Obstacle ob3 = { OBJSTACLETYPE_BOX, FVector( 300.0f, 0.0f, -200.0f ), FVector( 2.0f, 2.0f, 1.0f ) };
	rooms[0].obstacles.push_back( ob1 );
	rooms[0].obstacles.push_back( ob2 );
	rooms[0].obstacles.push_back( ob3 );
	rooms[0].timeLimit = 	12.0f;

	for ( unsigned int i = 0; i < s_cROOM_COUNT; ++i )
	{
		m_rooms.push( rooms[i] );
	}
}

void AOneRoomGameMode::GenerateRoom( void )
{
	if ( m_roomsCompleted < s_cROOM_COUNT )
	{

		m_roomsCompleted++;
		UE_LOG( DebugLog, Log, TEXT( "%i" ), m_roomsCompleted ); 
		m_pHUD->SetPercentage( static_cast<float>( m_roomsCompleted ) / static_cast<float>( s_cROOM_COUNT ) );
	}
	
	if ( m_rooms.empty() )
	{
		return;
		
	}

	Room& nextRoom = m_rooms.front();
	//m_pRoomObj->InitRoom( nextRoom );
	m_pRoomObj->UpdateScale( nextRoom.scale );
	m_pRoomObj->DetermineObstacles( nextRoom.obstacles );

	m_timeLimit = nextRoom.timeLimit;
	m_pPlayer->RoomChange( nextRoom );
	m_pGoal->UpdateLocation( nextRoom.endPoint );
	//m_pGoal->RoomChange( true, false, nextRoom.endPoint, FVector( 0.0f, 0.0f, 0.0f ) );
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
		if ( !m_pPlayer )
		{
			Log::LogStr( "Error: Missing object player in scene" );
		}

		if( !m_pGoal )
		{
			Log::LogStr( "Error: Missing object goal in scene" );
		}

		if ( !m_pRoomObj )
		{
			Log::LogStr( "Error: Missing object room in scene" );
		}
		return;
	}

	GenerateRoom();
}

void AOneRoomGameMode::StartPlay()
{
	Super::StartPlay();

	m_roomsCompleted = -1;
	m_pHUD = Cast<AOneRoomHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() );

	InitialiseQueue();
	InitRoom();
}