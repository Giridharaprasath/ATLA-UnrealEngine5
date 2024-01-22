// Developed By Melon Studios.

#include "SteamGameInstanceSubsystem.h"

#include "ATLAGameInstanceSubsystem.h"
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

void USteamGameInstanceSubsystem::OpenSteamUserUI(int FriendIndex)
{
	if (SteamSubsystem)
	{
		uint64 FriendSteamID = SteamFriends()->GetFriendByIndex(FriendIndex, k_EFriendFlagImmediate).ConvertToUint64();
		SteamFriends()->ActivateGameOverlayToUser("steamid", FriendSteamID);
	}
}

int USteamGameInstanceSubsystem::GetPlayerFriendsCount()
{
	int count = 0;
	if (SteamSubsystem)
	{
		count = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
	}

	if (count == -1)
	{
		return 0;
	}
	return count;
}

int64 USteamGameInstanceSubsystem::GetFriendSteamID(int FriendIndex)
{
	if (!SteamSubsystem)
	{
		return -1;
	}

	uint64 FriendSteamID = SteamFriends()->GetFriendByIndex(FriendIndex, k_EFriendFlagImmediate).ConvertToUint64();
	return FriendSteamID;
}

FString USteamGameInstanceSubsystem::GetFriendSteamName(int FriendIndex)
{
	if (GetPlayerFriendsCount() == 0)
	{
		return FString(TEXT(" "));
	}

	uint64 FriendSteamID = SteamFriends()->GetFriendByIndex(FriendIndex, k_EFriendFlagImmediate).ConvertToUint64();
	FString FriendStreamName = SteamFriends()->GetFriendPersonaName(FriendSteamID);
	
	return FString(FriendStreamName);
}

UTexture2D* USteamGameInstanceSubsystem::GetFriendSteamAvatar(int FriendIndex)
{
	uint32 Width = 0;
	uint32 Height = 0;

	if (SteamAPI_Init())
	{
		if (SteamUser())
		{
			uint64 FriendSteamID = SteamFriends()->GetFriendByIndex(FriendIndex, k_EFriendFlagImmediate).ConvertToUint64();
			
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

bool USteamGameInstanceSubsystem::GetFriendPersonaState(int FriendIndex)
{
	if (!SteamSubsystem)
	{
		return false;
	}

	uint64 FriendSteamID = SteamFriends()->GetFriendByIndex(FriendIndex, k_EFriendFlagImmediate).ConvertToUint64();
	EPersonaState FriendState = SteamFriends()->GetFriendPersonaState(FriendSteamID);
	if (FriendState == k_EPersonaStateOnline)
	{
		return true;
	}
	
	return false;
}

bool USteamGameInstanceSubsystem::GetFriendGamePlayed(int FriendIndex)
{
	if (!SteamSubsystem)
	{
		return false;
	}

	uint64 FriendSteamID = SteamFriends()->GetFriendByIndex(FriendIndex, k_EFriendFlagImmediate).ConvertToUint64();
	FriendGameInfo_t GameInfo;
	bool FriendGamePlayed = SteamFriends()->GetFriendGamePlayed(FriendSteamID, &GameInfo);
	if (FriendGamePlayed)
	{
		if (GameInfo.m_gameID.AppID() == 480)
		{
			return true;
		}
	}
	return false;
}

void USteamGameInstanceSubsystem::SetRichPresence(FString Key, FString Value)
{
	if (SteamSubsystem)
	{
		SteamFriends()->SetRichPresence(TCHAR_TO_ANSI(*Key), TCHAR_TO_ANSI(*Value));
	}
}

FString USteamGameInstanceSubsystem::GetFriendRichPresence(int FriendIndex, FString Key)
{
	if (SteamSubsystem)
	{
		uint64 FriendSteamID = SteamFriends()->GetFriendByIndex(FriendIndex, k_EFriendFlagImmediate).ConvertToUint64();
		const char* Value = SteamFriends()->GetFriendRichPresence(FriendSteamID, TCHAR_TO_ANSI(*Key));
		return FString(Value);
	}
	return FString(TEXT(""));
}

void USteamGameInstanceSubsystem::ClearRichPresence()
{
	if (SteamSubsystem)
	{
		SteamFriends()->ClearRichPresence();
	}
}