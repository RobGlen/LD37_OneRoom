// Fill out your copyright notice in the Description page of Project Settings.

#include "LD37_OneRoom.h"
#include "Log.h"

DEFINE_LOG_CATEGORY( DebugLog )

void Log::LogStr( FString str )
{
	UE_LOG( DebugLog, Log, TEXT( "%s" ), *str );
}

/*Log::Log()
{
}

Log::~Log()
{
}*/
