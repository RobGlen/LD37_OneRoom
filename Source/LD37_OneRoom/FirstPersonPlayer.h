// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FirstPersonPlayer.generated.h"

struct Room;
class AOneRoomHUD;
/**
 * 
 */
UCLASS()
class LD37_ONEROOM_API AFirstPersonPlayer : public ACharacter
{
	GENERATED_BODY()
	
private:
	AActor* m_pGoal = nullptr;
	AOneRoomHUD* m_pHUD = nullptr;
	//ARoom* m_pRoom = nullptr;

	bool m_updateLocation;
	FVector m_currentLocation;
	FVector m_targetLocation;
	float m_lerpSpeed;
	float m_timeLerped;
	float m_timeToLerp;
	bool m_buttonReady;
	

public:
	AFirstPersonPlayer( const FObjectInitializer& ObjectInitializer );
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void RoomChange( const Room& roomDesc );
	virtual void Tick( float DeltaSeconds ) override;

	void MoveForward( float speed );
	void MoveRight( float speed );
	void OnStartJump( void );
	void OnStopJump( void );
	void TestGoal( void );
	void Quit( void );
	//void SetRoom( ARoom* p_room ) { m_pRoom = p_room; }
	
	void SetGoal( AActor* p_goal ) { m_pGoal = p_goal; }
	
};
