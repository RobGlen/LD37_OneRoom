// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoomActor.generated.h"

struct Room;

struct RoomActorTransform
{
	FVector location;
	FVector rotation;
	FVector scale;
};

UCLASS()
class LD37_ONEROOM_API ARoomActor : public AActor
{
	GENERATED_BODY()

protected:
	bool m_updateLocation;
	bool m_updateScale;
	RoomActorTransform m_currentTransform;
	RoomActorTransform m_targetTransform;
	float m_lerpSpeed;

public:	
	// Sets default values for this actor's properties
	ARoomActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	void UpdateLocation( FVector location );
	void UpdateScale( FVector scale );

	void LerpLocation( float DeltaTime );
	void LerpScale( float DeltaTime );
	void Lerp( FVector& current, FVector& target, bool& update, float DeltaTime );
};
