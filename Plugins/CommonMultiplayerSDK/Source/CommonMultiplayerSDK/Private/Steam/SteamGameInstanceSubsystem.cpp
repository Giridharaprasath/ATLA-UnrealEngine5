// Copyright Melon Studios.

#include "Steam/SteamGameInstanceSubsystem.h"
#include "CommonMultiplayerSDK.h"
#include "OnlineSubsystem.h"
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
		SteamSubsystem = IOnlineSubsystem::Get(FName("SteamGameInstance"));
		PlayerSteamID = SteamUser()->GetSteamID().ConvertToUint64();
		PlayerSteamName = SteamFriends()->GetPersonaName();

		UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Steam Status : %hhd"), bSteamIsOnline);

		if (PlayerSteamID)
		{
			UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Player Steam ID : %llu"), PlayerSteamID);
		}
		if (!PlayerSteamName.IsEmpty())
		{
			UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Player Steam Name : %s"), *PlayerSteamName);
		}
	}
}

bool USteamGameInstanceSubsystem::GetSteamIsOnline() const
{
	return bSteamIsOnline;
}

FString USteamGameInstanceSubsystem::GetPlayerSteamName() const
{
	return PlayerSteamName;
}

UTexture2D* USteamGameInstanceSubsystem::GetPlayerSteamAvatar() const
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

					PlatformData->SetNumSlices(1);
					Avatar->NeverStream = true;
				}
				
				delete[] oAvatarRGBA;

				Avatar->UpdateResource();

				return Avatar;
			}
		}
	}

	return nullptr;
}

void USteamGameInstanceSubsystem::OpenSteamOverlayUI() const
{
	if (SteamSubsystem)
	{
		SteamFriends()->ActivateGameOverlay("Friends");
	}
}

void USteamGameInstanceSubsystem::OpenSteamInviteUI() const
{
	if (SteamSubsystem)
	{
		SteamFriends()->ActivateGameOverlay("LobbyInvite");
	}
}
