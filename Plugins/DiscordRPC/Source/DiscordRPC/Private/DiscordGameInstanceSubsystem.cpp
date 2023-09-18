// Developed By Melon Studios.

#include "DiscordGameInstanceSubsystem.h"
#include "discord_rpc.h"
#include <time.h>

void UDiscordGameInstanceSubsystem::InitiateDiscord(const FString& ApplicationID, bool bAutoRegister, const FString& SteamID)
{
	IsConnected = false;
	DiscordEventHandlers Handlers{};
	auto AppId = StringCast<ANSICHAR>(*ApplicationID);
	auto SteamId = StringCast<ANSICHAR>(*SteamID);
	Discord_Initialize(AppId.Get(), &Handlers, bAutoRegister, SteamId.Get());
	
	SetRPCLargeImageKey("gameicon");
	SetRPCLargeImageText("ATLA");
	StartTimeStamp();
	
	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::ShutdownDiscord()
{
	Discord_Shutdown();
}

void UDiscordGameInstanceSubsystem::UpdateDiscordPresence()
{
	DiscordRichPresence DiscordRichPresence;

	auto State = StringCast<ANSICHAR>(*RichPresence.State);
	DiscordRichPresence.state = State.Get();

	auto Details = StringCast<ANSICHAR>(*RichPresence.Details);
	DiscordRichPresence.details = Details.Get();

	auto LargeImageKey = StringCast<ANSICHAR>(*RichPresence.LargeImageKey);
	DiscordRichPresence.largeImageKey = LargeImageKey.Get();

	auto LargeImageText = StringCast<ANSICHAR>(*RichPresence.LargeImageText);
	DiscordRichPresence.largeImageText = LargeImageText.Get();

	auto SmallImageKey = StringCast<ANSICHAR>(*RichPresence.SmallImageKey);
	DiscordRichPresence.smallImageKey = SmallImageKey.Get();

	auto SmallImageText = StringCast<ANSICHAR>(*RichPresence.SmallImageText);
	DiscordRichPresence.smallImageText = SmallImageText.Get();

	auto PartyId = StringCast<ANSICHAR>(*RichPresence.PartyId);
	DiscordRichPresence.partyId = PartyId.Get();

	auto MatchSecret = StringCast<ANSICHAR>(*RichPresence.MatchSecret);
	DiscordRichPresence.matchSecret = MatchSecret.Get();

	auto JoinSecret = StringCast<ANSICHAR>(*RichPresence.JoinSecret);
	DiscordRichPresence.joinSecret = JoinSecret.Get();

	auto SpectateSecret = StringCast<ANSICHAR>(*RichPresence.SpectateSecret);
	DiscordRichPresence.spectateSecret = SpectateSecret.Get();
	DiscordRichPresence.startTimestamp = RichPresence.StartTimestamp;
	DiscordRichPresence.endTimestamp = RichPresence.EndTimestamp;
	DiscordRichPresence.partySize = RichPresence.PartySize;
	DiscordRichPresence.partyMax = RichPresence.PartyMax;
	DiscordRichPresence.instance = RichPresence.bInstance;
	
	Discord_UpdatePresence(&DiscordRichPresence);	
}

void UDiscordGameInstanceSubsystem::SetRPCState(const FString& CurrentState)
{
	RichPresence.State = CurrentState;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCDetails(const FString& CurrentDetails)
{
	RichPresence.Details = CurrentDetails;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCLargeImageKey(const FString& CurrentLargeImageKey)
{
	RichPresence.LargeImageKey = CurrentLargeImageKey;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCLargeImageText(const FString& CurrentLargeImageText)
{
	RichPresence.LargeImageText = CurrentLargeImageText;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCSmallImageKey(const FString& CurrentSmallImageKey)
{
	RichPresence.SmallImageKey = CurrentSmallImageKey;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCSmallImageText(const FString& CurrentSmallImageText)
{
	RichPresence.SmallImageText = CurrentSmallImageText;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCPartySize(int CurrentPartySize)
{
	RichPresence.PartySize = CurrentPartySize;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::SetRPCPartyMax(int CurrentPartyMax)
{
	RichPresence.PartyMax = CurrentPartyMax;

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::ResetDiscordPresence()
{
	RichPresence.Details = "";
	RichPresence.State = "";
	RichPresence.PartyMax = 0;
	RichPresence.PartySize = 0;
	RichPresence.SmallImageKey = "";
	RichPresence.SmallImageText = "";

	UpdateDiscordPresence();
}

void UDiscordGameInstanceSubsystem::StartTimeStamp()
{
	time_t StartTime;
	time(&StartTime);

	RichPresence.StartTimestamp = StartTime;

	UpdateDiscordPresence();
}