// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamGameInstanceSubsystem.h"

#include "steam/steam_api.h"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4265)
#endif

USteamGameInstanceSubsystem::USteamGameInstanceSubsystem()
{
	if (SteamAPI_Init())
	{
		bSteamIsOnline = SteamUser()->BLoggedOn();
		SteamSubsystem = IOnlineSubsystem::Get(FName("Steam"));
		PlayerSteamID = SteamUser()->GetSteamID().ConvertToUint64();
		PlayerSteamName = SteamFriends()->GetPersonaName();
		if (PlayerSteamID)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Cyan,
				FString::Printf(TEXT("Player Steam ID: %llu"), PlayerSteamID));
			}
		}
		if (!PlayerSteamName.IsEmpty())
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Cyan,
				FString::Printf(TEXT("Player Steam Name: %s"), *PlayerSteamName));
			}
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Cyan,
				FString::Printf(TEXT("Player Status %hhd"), bSteamIsOnline));
		}
	}
}

bool USteamGameInstanceSubsystem::GetSteamIsOnline()
{
	return bSteamIsOnline;
}

FString USteamGameInstanceSubsystem::GetPlayerSteamID()
{
	if (PlayerSteamID)
	{
		return FString::Printf(TEXT("%llu"), PlayerSteamID);
	}
	return FString(TEXT(" "));
}

FString USteamGameInstanceSubsystem::GetPlayerSteamName()
{
	if (!PlayerSteamName.IsEmpty())
	{
		return FString(PlayerSteamName);
	}
	return FString(TEXT(" "));
}

void USteamGameInstanceSubsystem::OpenSteamInviteUI()
{
	if (SteamSubsystem)
	{
		SteamFriends()->ActivateGameOverlay("LobbyInvite");
		
		//SteamFriends()->ActivateGameOverlayInviteDialog()
	}
}

void USteamGameInstanceSubsystem::OpenSteamOverlayUI()
{
	if (SteamSubsystem)
	{
		SteamFriends()->ActivateGameOverlay("Friends");
	}
}

