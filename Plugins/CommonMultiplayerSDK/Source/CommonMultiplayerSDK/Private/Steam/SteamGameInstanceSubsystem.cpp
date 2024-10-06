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
		SteamSubsystem = IOnlineSubsystem::Get(FName("Steam"));
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
	if (bSteamIsOnline)
	{
		SteamFriends()->ActivateGameOverlay("Friends");
	}
}

void USteamGameInstanceSubsystem::OpenSteamInviteUI() const
{
	if (bSteamIsOnline)
	{
		SteamFriends()->ActivateGameOverlay("LobbyInvite");
	}
}

void USteamGameInstanceSubsystem::SetRichPresence(const FString& Key, const FString& Value) const
{
	if (bSteamIsOnline)
	{
		SteamFriends()->SetRichPresence(TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
	}
}

int USteamGameInstanceSubsystem::GetPlayerFriendsCount() const
{
	if (bSteamIsOnline)
	{
		return SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
	}
	
	return 0;
}

int64 USteamGameInstanceSubsystem::GetFriendSteamID(const int FriendIndex) const
{
	if (bSteamIsOnline)
	{
		return SteamFriends()->GetFriendByIndex(FriendIndex, k_EFriendFlagImmediate).ConvertToUint64();
	}
	return -1;
}

FString USteamGameInstanceSubsystem::GetFriendSteamName(const int FriendIndex) const
{
	if (bSteamIsOnline)
	{
		const uint64 FriendSteamID = GetFriendSteamID(FriendIndex);
		return  SteamFriends()->GetFriendPersonaName(FriendSteamID);
	}
	
	return FString();
}

UTexture2D* USteamGameInstanceSubsystem::GetFriendSteamAvatar(const int FriendIndex) const
{
	uint32 Width = 0;
	uint32 Height = 0;

	if (SteamAPI_Init())
	{
		if (SteamUser())
		{
			uint64 FriendSteamID = GetFriendSteamID(FriendIndex);
			int Picture = SteamFriends()->GetMediumFriendAvatar(FriendSteamID);

			SteamUtils()->GetImageSize(Picture, &Width, &Height);
		
			if (Width > 0 && Height > 0)
			{
				uint8* oAvatarRGBA = new uint8[Width * Height * 4];
				
				SteamUtils()->GetImageRGBA(Picture, oAvatarRGBA, 4 * Width * Height * sizeof(char));

				UTexture2D* Avatar = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);

				if (FTexturePlatformData* PlatformData = Avatar->GetPlatformData())
				{
					uint8* MipData = (uint8*)PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(MipData, oAvatarRGBA, Height * Width * 4);
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

bool USteamGameInstanceSubsystem::GetFriendPersonaState(const int FriendIndex) const
{
	if (bSteamIsOnline)
	{
		const uint64 FriendSteamID = GetFriendSteamID(FriendIndex);
		const EPersonaState FriendState = SteamFriends()->GetFriendPersonaState(FriendSteamID);
		return FriendState == k_EPersonaStateOnline;
	}

	return false;
}

bool USteamGameInstanceSubsystem::GetFriendGamePlayed(const int FriendIndex) const
{
	if (bSteamIsOnline)
	{
		const uint64 FriendSteamID = GetFriendSteamID(FriendIndex);
		FriendGameInfo_t GameInfo;
		if (SteamFriends()->GetFriendGamePlayed(FriendSteamID, &GameInfo))
		{
			if (GameInfo.m_gameID.AppID() == 480)
				return true;
		}
	}

	return false;
}

