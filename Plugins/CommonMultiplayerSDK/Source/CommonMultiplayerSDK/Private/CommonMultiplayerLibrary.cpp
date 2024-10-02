// Copyright Melon Studios.

#include "CommonMultiplayerLibrary.h"
#include "CommonMultiplayerSDK.h"
#include "MultiplayerGameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UCommonMultiplayerLibrary::CreateMultiplayerSession(const UObject* WorldContextObject, ULocalPlayer* LocalPlayer,
                                                         FSessionSettingsInfo SessionSettingsInfo)
{
	GetMultiplayerGameInstanceSubsystem(WorldContextObject)->CreateMultiplayerSession(LocalPlayer, SessionSettingsInfo);
}

UMultiplayerGameInstanceSubsystem* UCommonMultiplayerLibrary::GetMultiplayerGameInstanceSubsystem(
	const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UMultiplayerGameInstanceSubsystem>();
}
