// Copyright Melon Studios.

#include "CommonMultiplayerLibrary.h"
#include "CommonMultiplayerSDK.h"
#include "MultiplayerGameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Steam/SteamBlueprintFunctionLibrary.h"

void UCommonMultiplayerLibrary::CreateMultiplayerSession(const UObject* WorldContextObject, ULocalPlayer* LocalPlayer, const FSessionSettingsInfo SessionSettingsInfo)
{
	GetMultiplayerGameInstanceSubsystem(WorldContextObject)->CreateMultiplayerSession(LocalPlayer, SessionSettingsInfo);
}

void UCommonMultiplayerLibrary::DestroyMultiplayerSession(const UObject* WorldContextObject)
{
	GetMultiplayerGameInstanceSubsystem(WorldContextObject)->DestroyMultiplayerSession();
}

void UCommonMultiplayerLibrary::FindMultiplayerSession(const UObject* WorldContextObject, const bool bUseLan, const FString LobbyName)
{
	GetMultiplayerGameInstanceSubsystem(WorldContextObject)->FindMultiplayerSession(bUseLan, LobbyName);
}

bool UCommonMultiplayerLibrary::UseLanMode(const UObject* WorldContextObject)
{
	bool bUseLanMode = true;

	if (USteamBlueprintFunctionLibrary::GetSteamIsOnline(WorldContextObject))
	{
		bUseLanMode = false;
	}

	return bUseLanMode;
}

FOnSessionProcessSignature UCommonMultiplayerLibrary::OnCreateStartSessionProcessDelegate;
FOnSessionProcessSignature UCommonMultiplayerLibrary::OnFindJoinSessionProcessDelegate;

UMultiplayerGameInstanceSubsystem* UCommonMultiplayerLibrary::GetMultiplayerGameInstanceSubsystem(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UMultiplayerGameInstanceSubsystem>();
}
