// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "GameFramework/Actor.h"
#include "RoomActor.h"
#include "Room.generated.h"

struct Room;
struct Obstacle;
class ARoomActor;

UCLASS()
class LD37_ONEROOM_API ARoom : public ARoomActor
{
	GENERATED_BODY()
private:
	std::vector<ARoomActor*> m_obstacles;

public:	
	UStaticMeshComponent* Mesh;

	// Sets default values for this actor's properties
	ARoom( const FObjectInitializer& foi );

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void DetermineObstacles( std::vector<Obstacle>& obstacles );
};
