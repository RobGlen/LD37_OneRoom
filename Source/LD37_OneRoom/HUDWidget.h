// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class LD37_ONEROOM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
private:

public:
	UHUDWidget( const FObjectInitializer& foi );
	~UHUDWidget( void );
	
	UFUNCTION( BlueprintImplementableEvent )
	void DetermineInteract( ESlateVisibility interactVisibility );

	UFUNCTION( BlueprintImplementableEvent )
	void SetPercentage( float percent );
};
