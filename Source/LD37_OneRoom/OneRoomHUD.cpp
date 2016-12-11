// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "OneRoomHUD.h"
#include "HUDWidget.h"
#include "Log.h"

AOneRoomHUD::AOneRoomHUD( const FObjectInitializer& foi )
{
	//WidgetBlueprint'/Game/Blueprints/UMG_HUD.UMG_HUD'
	//m_currentWidget = LoadClass<UHUDWidget>( )
}

AOneRoomHUD::~AOneRoomHUD( void )
{

}

void AOneRoomHUD::BeginPlay()
{
	Super::BeginPlay();
	m_visible = true;
	Log::LogStr( "HUD started" );
	m_startingWidgetClass = LoadClass<UHUDWidget>( NULL, TEXT( "/Game/Blueprints/UMGHUD.UMGHUD_C" ), NULL, LOAD_None, NULL );
	ChangeMenuWidget( m_startingWidgetClass );
	ToggleInteractVisibility( false );
}

void AOneRoomHUD::ChangeMenuWidget( TSubclassOf<UHUDWidget> newWidgetClass )
{
	if ( m_currentWidget )
	{
		Log::LogStr( "Removing old HUD" );
		m_currentWidget->RemoveFromViewport();
		m_currentWidget = nullptr;
	}

	if ( newWidgetClass )
	{
		Log::LogStr( "Adding new HUD" );
		m_currentWidget = CreateWidget<UHUDWidget>( GetWorld(), newWidgetClass );
		if ( m_currentWidget )
		{
			m_currentWidget->AddToViewport();
		}
	}
	else
	{
		Log::LogStr( "No hud widget to create" );
	}
}

void AOneRoomHUD::ToggleInteractVisibility( bool visible )
{
	if ( m_visible != visible )
	{
		ESlateVisibility visibility = ( visible ) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
		m_currentWidget->DetermineInteract( visibility );
		m_visible = visible;
	}
}

void AOneRoomHUD::SetPercentage( float percent )
{
	m_currentWidget->SetPercentage( percent );
}