// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "FirstPersonPlayer.h"
#include "Room.h"
#include "LD37_OneRoomGameMode.h"
#include "Log.h"
#include "OneRoomHUD.h"

AFirstPersonPlayer::AFirstPersonPlayer( const FObjectInitializer& foi )
{
	PrimaryActorTick.bCanEverTick = true;
	m_updateLocation = false;
	m_currentLocation = GetActorLocation();
	m_targetLocation = GetActorLocation();
	m_lerpSpeed = 2.0f;
	m_timeLerped = 0.0f;
	m_timeToLerp = m_lerpSpeed;
	m_buttonReady = false;
}

void AFirstPersonPlayer::BeginPlay()
{
	Super::BeginPlay();
	m_pHUD = Cast<AOneRoomHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() );
}

void AFirstPersonPlayer::SetupPlayerInputComponent( class UInputComponent* InputComponent )
{
	Super::SetupPlayerInputComponent( InputComponent );
	InputComponent->BindAxis( "MoveForward", this, &AFirstPersonPlayer::MoveForward );
    InputComponent->BindAxis( "MoveRight", this, &AFirstPersonPlayer::MoveRight );
	InputComponent->BindAxis( "HorizontalLook", this, &AFirstPersonPlayer::AddControllerYawInput );
	InputComponent->BindAxis( "VerticalLook", this, &AFirstPersonPlayer::AddControllerPitchInput );
	InputComponent->BindAction( "Jump", IE_Pressed, this, &AFirstPersonPlayer::OnStartJump );
	InputComponent->BindAction( "Jump", IE_Released, this, &AFirstPersonPlayer::OnStopJump );
	InputComponent->BindAction( "Interact", IE_Pressed, this, &AFirstPersonPlayer::TestGoal );
	InputComponent->BindAction( "Quit", IE_Pressed, this, &AFirstPersonPlayer::Quit );
}

void AFirstPersonPlayer::RoomChange( const Room& roomDesc )
{
	m_updateLocation = true;
	SetActorEnableCollision( false );
	m_currentLocation = GetActorLocation();
	m_targetLocation = roomDesc.startPoint;
	m_timeLerped = 0.0f;
	m_timeToLerp = m_lerpSpeed;
}

void AFirstPersonPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if ( m_updateLocation )
	{
		SetActorLocation( m_currentLocation );
		m_timeLerped += DeltaTime;
		m_currentLocation = FMath::Lerp( m_currentLocation, m_targetLocation, m_timeLerped / m_timeToLerp );
		
		if ( ( m_targetLocation - m_currentLocation ).Size() <= 0.2f )
		{
			Log::LogStr( "Lerp successful" );
			m_updateLocation = false;
			SetActorEnableCollision( true );
		}
	}

	if ( m_pGoal )
	{
		FVector goalPos = m_pGoal->GetActorLocation();
		FVector pos = GetActorLocation();
		FVector delta = goalPos - pos;
		
		if ( delta.SizeSquared() <= 14400.0f )
		{
			delta.Normalize();
			float dot = FVector::DotProduct( GetActorForwardVector(), delta );
			m_buttonReady = dot > 0.7f;
			//UE_LOG( DebugLog, Log, TEXT( "%f"), dot );

			m_pHUD->ToggleInteractVisibility( m_buttonReady );
		}
		else
		{
			m_pHUD->ToggleInteractVisibility( false );
			m_buttonReady = false;
		}
	}
}

void AFirstPersonPlayer::MoveForward( float speed )
{
	if ( ( Controller != NULL ) && ( speed != 0.0f ) )
    {
        // find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();

        // Limit pitch when walking or falling
        if ( GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling() )
        {
            Rotation.Pitch = 0.0f;
        }

        // add movement in that direction
        const FVector Direction = FRotationMatrix( Rotation ).GetScaledAxis( EAxis::X );
        AddMovementInput( Direction, speed );
    }
}

void AFirstPersonPlayer::MoveRight( float speed )
{
	if ( ( Controller != NULL ) && ( speed != 0.0f ) )
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix( Rotation ).GetScaledAxis( EAxis::Y );
        // add movement in that direction
        AddMovementInput( Direction, speed );
    }
}

void AFirstPersonPlayer::OnStartJump( void )
{
	bPressedJump = true;
}

void AFirstPersonPlayer::OnStopJump( void )
{
	bPressedJump = false;
}

void AFirstPersonPlayer::TestGoal( void )
{
	//Log::LogStr( "Interacting" );	
	if ( m_buttonReady )
	{
		//m_pRoom->GenerateRoom();
		AOneRoomGameMode* p_gamemode = ( AOneRoomGameMode* )( GetWorld()->GetAuthGameMode() );
		p_gamemode->GenerateRoom();
		Log::LogStr( "Generating next room" );
	}
}

void AFirstPersonPlayer::Quit( void )
{
	Log::LogStr( "Quit" );
	UKismetSystemLibrary::QuitGame( GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit );
}