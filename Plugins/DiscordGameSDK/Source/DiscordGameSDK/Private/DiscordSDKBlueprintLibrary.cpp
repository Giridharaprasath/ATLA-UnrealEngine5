// Copyright Melon Studios.

#include "DiscordSDKBlueprintLibrary.h"
#include "DiscordGameInstanceSubsystem.h"
#include "DiscordGameSDK.h"
#include "Kismet/GameplayStatics.h"

void UDiscordSDKBlueprintLibrary::DiscordSetActivity(const UObject* WorldContextObject,
                                                     const FDiscordActivity& DiscordActivity)
{
	if (UDiscordGameInstanceSubsystem* DiscordGameIS = GetDiscordGameInstanceSubsystem(WorldContextObject);
		DiscordGameIS)
	{
		DiscordGameIS->SetActivity(DiscordActivity);
	}
	else
	{
		UE_LOG(LogDiscordGameSDK, Log, TEXT("Discord Game SDK Game Instance Subsystem Not Found, Error!!"));
	}
}

void UDiscordSDKBlueprintLibrary::DiscordResetActivity(const UObject* WorldContextObject)
{
	if (UDiscordGameInstanceSubsystem* DiscordGameIS = GetDiscordGameInstanceSubsystem(WorldContextObject);
		DiscordGameIS)
	{
		DiscordGameIS->ResetActivity();
	}
	else
	{
		UE_LOG(LogDiscordGameSDK, Log, TEXT("Discord Game SDK Game Instance Subsystem Not Found, Error!!"));
	}
}

void UDiscordSDKBlueprintLibrary::DiscordClearActivity(const UObject* WorldContextObject)
{
	if (UDiscordGameInstanceSubsystem* DiscordGameIS = GetDiscordGameInstanceSubsystem(WorldContextObject);
		DiscordGameIS)
	{
		DiscordGameIS->ClearActivity();
	}
	else
	{
		UE_LOG(LogDiscordGameSDK, Log, TEXT("Discord Game SDK Game Instance Subsystem Not Found, Error!!"));
	}
}

UDiscordGameInstanceSubsystem* UDiscordSDKBlueprintLibrary::GetDiscordGameInstanceSubsystem(
	const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UDiscordGameInstanceSubsystem>();
}
