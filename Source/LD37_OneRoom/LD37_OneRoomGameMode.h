// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <queue>
#include "GameFramework/GameMode.h"
#include "LD37_OneRoomGameMode.generated.h"

class ARoom;

enum ObstacleType
{
	OBJSTACLETYPE_BOX, OBJSTACLETYPE_TURRET, 
};

struct Obstacle
{
	ObstacleType obstacleType;
	FVector position;
	FVector scale;
};

struct Room
{
	FVector startPoint;
	FRotator orientation;
	FVector endPoint;
	FVector scale;
	std::vector<Obstacle> obstacles;
	float timeLimit;
};


/**
 * 
 */
UCLASS()
class LD37_ONEROOM_API AOneRoomGameMode : public AGameMode
{
	GENERATED_BODY()
private:
	static const int s_cROOM_COUNT;
	ARoom* m_pRoomObj = nullptr;
	std::queue<Room> m_rooms;
	float m_timeLimit;

	void InitialiseQueue( void );
	void GenerateRoom( void );
	void InitRoom( void );

public:
	AOneRoomGameMode( const FObjectInitializer& foi );
	~AOneRoomGameMode( void );
	virtual void StartPlay() override;
};
