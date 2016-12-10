// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FirstPersonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class LD37_ONEROOM_API AFirstPersonPlayer : public ACharacter
{
	GENERATED_BODY()
	
private:
	AActor* m_pGoal = nullptr;
	//ARoom* m_pRoom = nullptr;

public:
	AFirstPersonPlayer( const FObjectInitializer& ObjectInitializer );
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward( float speed );
	void MoveRight( float speed );
	void OnStartJump( void );
	void OnStopJump( void );
	void TestGoal( void );
	//void SetRoom( ARoom* p_room ) { m_pRoom = p_room; }
	void SetGoal( AActor* p_goal ) { m_pGoal = p_goal; }
};
