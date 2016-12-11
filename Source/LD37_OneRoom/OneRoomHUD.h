// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HUDWidget.h"
#include "GameFramework/HUD.h"
#include "OneRoomHUD.generated.h"

/**
 * 
 */
UCLASS()
class LD37_ONEROOM_API AOneRoomHUD : public AHUD
{
	GENERATED_BODY()
private:
	bool m_visible;

	UPROPERTY()
	UHUDWidget* m_currentWidget = nullptr;

public:
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "UMGGame" )
	TSubclassOf<UHUDWidget> m_startingWidgetClass;

	AOneRoomHUD( const FObjectInitializer& foi );
	~AOneRoomHUD( void );
	virtual void BeginPlay() override;
	//UFUNCTION( BlueprintCallable, Category = "UMGGame" )
	void ChangeMenuWidget( TSubclassOf<UHUDWidget> newWidgetClass );
	void ToggleInteractVisibility( bool visible );
	void SetPercentage( float percent );
};
