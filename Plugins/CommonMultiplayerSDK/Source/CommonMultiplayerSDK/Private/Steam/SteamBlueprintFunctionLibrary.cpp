// Copyright Melon Studios.

#include "Steam/SteamBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Steam/SteamGameInstanceSubsystem.h"

bool USteamBlueprintFunctionLibrary::GetSteamIsOnline(const UObject* WorldContextObject)
{
	return GetSteamGameInstanceSubsystem(WorldContextObject)->GetSteamIsOnline();
}

FString USteamBlueprintFunctionLibrary::GetPlayerSteamName(const UObject* WorldContextObject)
{
	return GetSteamGameInstanceSubsystem(WorldContextObject)->GetPlayerSteamName();
}

UTexture2D* USteamBlueprintFunctionLibrary::GetPlayerSteamAvatar(const UObject* WorldContextObject)
{
	return GetSteamGameInstanceSubsystem(WorldContextObject)->GetPlayerSteamAvatar();
}

void USteamBlueprintFunctionLibrary::OpenSteamOverlayUI(const UObject* WorldContextObject)
{
	return GetSteamGameInstanceSubsystem(WorldContextObject)->OpenSteamOverlayUI();
}

void USteamBlueprintFunctionLibrary::OpenSteamInviteUI(const UObject* WorldContextObject)
{
	return GetSteamGameInstanceSubsystem(WorldContextObject)->OpenSteamInviteUI();
}

int USteamBlueprintFunctionLibrary::GetPlayerFriendsCount(const UObject* WorldContextObject)
{
	return GetSteamGameInstanceSubsystem(WorldContextObject)->GetPlayerFriendsCount();
}

FString USteamBlueprintFunctionLibrary::GetFriendSteamName(const UObject* WorldContextObject, int FriendIndex)
{
	return GetSteamGameInstanceSubsystem(WorldContextObject)->GetFriendSteamName(FriendIndex);
}

UTexture2D* USteamBlueprintFunctionLibrary::GetFriendSteamAvatar(const UObject* WorldContextObject, int FriendIndex)
{
	return GetSteamGameInstanceSubsystem(WorldContextObject)->GetFriendSteamAvatar(FriendIndex);
}

USteamGameInstanceSubsystem* USteamBlueprintFunctionLibrary::GetSteamGameInstanceSubsystem(
	const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<USteamGameInstanceSubsystem>();
}
