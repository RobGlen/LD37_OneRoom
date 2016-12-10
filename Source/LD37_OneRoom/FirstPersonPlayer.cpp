// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "FirstPersonPlayer.h"
#include "Room.h"
#include "LD37_OneRoomGameMode.h"

AFirstPersonPlayer::AFirstPersonPlayer( const FObjectInitializer& foi )
{

}

void AFirstPersonPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstPersonPlayer::SetupPlayerInputComponent( class UInputComponent* InputComponent )
{
	InputComponent->BindAxis( "MoveForward", this, &AFirstPersonPlayer::MoveForward );
    InputComponent->BindAxis( "MoveRight", this, &AFirstPersonPlayer::MoveRight );
	InputComponent->BindAxis( "HorizontalLook", this, &AFirstPersonPlayer::AddControllerYawInput );
	InputComponent->BindAxis( "VerticalLook", this, &AFirstPersonPlayer::AddControllerPitchInput );
	InputComponent->BindAction( "Jump", IE_Pressed, this, &AFirstPersonPlayer::OnStartJump );
	InputComponent->BindAction( "Jump", IE_Released, this, &AFirstPersonPlayer::OnStopJump );
	InputComponent->BindAction( "Interact", IE_Pressed, this, &AFirstPersonPlayer::TestGoal );
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
	if ( m_pGoal )
	{
		FVector goalPos = m_pGoal->GetActorLocation();
		FVector pos = GetActorLocation();
		FVector delta = goalPos - pos;

		if ( delta.Size() <= 0.5f )
		{
			delta.Normalize();
			float dot = FVector::DotProduct( GetActorForwardVector(), delta );

			if ( dot > 0.0f )
			{
				//m_pRoom->GenerateRoom();
				AOneRoomGameMode* p_gamemode = ( AOneRoomGameMode* )( GetWorld()->GetAuthGameMode() );
				p_gamemode->GenerateRoom();
			}
		}
	}
}