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

UTexture2D* USteamGameInstanceSubsystem::GetPlayerSteamAvatar()
{
	uint32 Width = 0;
	uint32 Height = 0;

	if (SteamAPI_Init())
	{
		if (SteamUser())
		{
			int Picture = SteamFriends()->GetMediumFriendAvatar(SteamUser()->GetSteamID());

			SteamUtils()->GetImageSize(Picture, &Width, &Height);
		
			if (Width > 0 && Height > 0)
			{
				uint8* oAvatarRGBA = new uint8[Width * Height * 4];

				SteamUtils()->GetImageRGBA(Picture, (uint8*)oAvatarRGBA, 4 * Width * Height * sizeof(char));

				UTexture2D* Avatar = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);

				if (FTexturePlatformData* PlatformData = Avatar->GetPlatformData())
				{
					uint8* MipData = (uint8*)PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(MipData, (void*)oAvatarRGBA, Height * Width * 4);
					PlatformData->Mips[0].BulkData.Unlock();

					delete[] oAvatarRGBA;

					PlatformData->SetNumSlices(1);
					Avatar->NeverStream = true;
				}

				Avatar->UpdateResource();

				return Avatar;
			}
		}
	}

	return nullptr;
}

void USteamGameInstanceSubsystem::OpenSteamInviteUI()
{
	if (SteamSubsystem)
	{
		SteamFriends()->ActivateGameOverlay("LobbyInvite");
	}
}

void USteamGameInstanceSubsystem::OpenSteamOverlayUI()
{
	if (SteamSubsystem)
	{
		SteamFriends()->ActivateGameOverlay("Friends");
	}
}