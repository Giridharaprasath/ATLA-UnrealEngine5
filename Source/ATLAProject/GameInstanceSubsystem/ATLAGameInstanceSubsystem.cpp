// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAGameInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#include "steam/steam_api.h"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4265)
#endif

UATLAGameInstanceSubsystem::UATLAGameInstanceSubsystem()
{
    if (SteamAPI_Init())
    {
        
    }

    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Blue,
					FString::Printf(TEXT("SUBSYSTEM PRESENT: %s"), *Subsystem->GetSubsystemName().ToString()));
			}
		}
	}
}

bool UATLAGameInstanceSubsystem::HasOnlineSubsystem(FName SubsystemName)
{
    return IOnlineSubsystem::DoesInstanceExist(SubsystemName);
}
