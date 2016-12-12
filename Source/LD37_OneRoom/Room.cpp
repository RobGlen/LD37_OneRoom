// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "Room.h"
#include "LD37_OneRoomGameMode.h"
#include "Log.h"
#include "Obstacle.h"

// Sets default values
ARoom::ARoom( const FObjectInitializer& foi )
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	for ( TActorIterator<AObstacle> ActorItr( GetWorld() ); ActorItr; ++ActorItr )
	{
		m_obstacles.push_back( ( *ActorItr ) );
	}
}

// Called every frame
void ARoom::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void ARoom::DetermineObstacles( std::vector<Obstacle>& obstacles )
{
	for ( std::vector<ARoomActor*>::iterator itr = m_obstacles.begin(); itr != m_obstacles.end(); ++itr )
	{
		( *itr )->SetActorScale3D( FVector( 0.0f, 0.0f, 0.0f ) );
		( *itr )->SetActorEnableCollision( false );
	}

	for ( int i = 0; i < obstacles.size(); ++i )
	{
		if ( i < m_obstacles.size() )
		{
			m_obstacles[i]->UpdateLocation( obstacles[i].position );
			m_obstacles[i]->UpdateScale( obstacles[i].scale );
			m_obstacles[i]->SetActorEnableCollision( true );
		}
	}
	/*for ( std::vector<Obstacle>::iterator itr = obstacles.begin(); itr != obstacles.end(); ++itr )
	{
		Obstacle& obstacle = *itr;
		FRotator frot = FRotator( 0.0f, 0.0f, 0.0f );
		FActorSpawnParameters spawnDesc;
		ARoomActor* p_roomactor = ( ARoomActor* )( GetWorld()->SpawnActor<ARoomActor>( ARoomActor::StaticClass(), obstacle.position, frot, spawnDesc ) );
		//p_roomactor->AddComponent(  )
		TSubclassOf<UStaticMesh> statmesh = LoadClass<UStaticMesh>( NULL, TEXT( "/Engine/BasicShapes/Cube.Cube" ), NULL, LOAD_None, NULL );
		//GetWorld()->SpawnActor( )
		p_roomactor->AddComponent( FName( "Box" ), false, FTransform(), statmesh );
		
		//GetWorld()->SpawnActor( ABox::StaticClass() );
		//'/Engine/BasicShapes/Cube.Cube'
		p_roomactor->SetActorScale3D( FVector( 0.0f, 0.0f, 0.0f ) );
		p_roomactor->UpdateScale( obstacle.scale );
		m_obstacles.push_back( p_roomactor );
	}*/
}