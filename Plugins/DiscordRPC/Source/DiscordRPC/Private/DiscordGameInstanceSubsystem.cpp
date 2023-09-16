// Developed By Melon Studios.

#include "DiscordGameInstanceSubsystem.h"
#include "discord_rpc.h"
#include <time.h>

void UDiscordGameInstanceSubsystem::InitiateDiscord(const FString& applicationId, bool autoRegister, const FString& optionalSteamId)
{
	IsConnected = false;
	DiscordEventHandlers Handlers{};
	auto appId = StringCast<ANSICHAR>(*applicationId);
	auto steamId = StringCast<ANSICHAR>(*optionalSteamId);
	Discord_Initialize((const char*)appId.Get(), &Handlers, autoRegister, (const char*)steamId.Get());
	
	SetRPCLargeImageKey("gameicon");
	StartTimeStamp();
	
	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::ShutdownDiscord()
{
	Discord_Shutdown();
}

void UDiscordGameInstanceSubsystem::UpdateDiscordPresence()
{
	DiscordRichPresence DiscordRichPresence{};
	
	auto state = StringCast<ANSICHAR>(*RichPresence.state);
	DiscordRichPresence.state = state.Get();

	auto details = StringCast<ANSICHAR>(*RichPresence.details);
	DiscordRichPresence.details = details.Get();

	auto largeImageKey = StringCast<ANSICHAR>(*RichPresence.largeImageKey);
	DiscordRichPresence.largeImageKey = largeImageKey.Get();

	auto largeImageText = StringCast<ANSICHAR>(*RichPresence.largeImageText);
	DiscordRichPresence.largeImageText = largeImageText.Get();

	auto smallImageKey = StringCast<ANSICHAR>(*RichPresence.smallImageKey);
	DiscordRichPresence.smallImageKey = smallImageKey.Get();

	auto smallImageText = StringCast<ANSICHAR>(*RichPresence.smallImageText);
	DiscordRichPresence.smallImageText = smallImageText.Get();

	auto partyId = StringCast<ANSICHAR>(*RichPresence.partyId);
	DiscordRichPresence.partyId = partyId.Get();

	auto matchSecret = StringCast<ANSICHAR>(*RichPresence.matchSecret);
	DiscordRichPresence.matchSecret = matchSecret.Get();

	auto joinSecret = StringCast<ANSICHAR>(*RichPresence.joinSecret);
	DiscordRichPresence.joinSecret = joinSecret.Get();

	auto spectateSecret = StringCast<ANSICHAR>(*RichPresence.spectateSecret);
	DiscordRichPresence.spectateSecret = spectateSecret.Get();
	DiscordRichPresence.startTimestamp = RichPresence.startTimestamp;
	DiscordRichPresence.endTimestamp = RichPresence.endTimestamp;
	DiscordRichPresence.partySize = RichPresence.partySize;
	DiscordRichPresence.partyMax = RichPresence.partyMax;
	DiscordRichPresence.instance = RichPresence.instance;
	
	Discord_UpdatePresence(&DiscordRichPresence);	
}

void UDiscordGameInstanceSubsystem::SetRPCState(const FString& CurrentState)
{
	RichPresence.state = CurrentState;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCDetails(const FString& CurrentDetails)
{
	RichPresence.details = CurrentDetails;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCLargeImageKey(const FString& CurrentLargeImageKey)
{
	RichPresence.largeImageKey = CurrentLargeImageKey;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCLargeImageText(const FString& CurrentLargeImageText)
{
	RichPresence.largeImageText = CurrentLargeImageText;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCSmallImageKey(const FString& CurrentSmallImageKey)
{
	RichPresence.smallImageKey = CurrentSmallImageKey;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCSmallImageText(const FString& CurrentSmallImageText)
{
	RichPresence.smallImageText = CurrentSmallImageText;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCPartySize(int CurrentPartySize)
{
	RichPresence.partySize = CurrentPartySize;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCPartyMax(int CurrentPartyMax)
{
	RichPresence.partyMax = CurrentPartyMax;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::StartTimeStamp()
{
	time_t StartTime;
	time(&StartTime);

	RichPresence.startTimestamp = StartTime;

	UpdateDiscordPresence();
}