// Copyright Melon Studios.

#include "Game/ATLAGameInstance.h"
#include "ATLA/ATLA.h"
#include "Kismet/GameplayStatics.h"
#include "CommonMultiplayerLibrary.h"
#include "CommonMultiplayerSDK.h"

void UATLAGameInstance::ExitToDesktop_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("Exit To Desktop"));

	DestroyATLASession();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->ConsoleCommand("quit");
	}
}

void UATLAGameInstance::ExitToMainMenu_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("Exit To Main Menu Level"));

	DestroyATLASession();
	GoToMainMenuLevel();
}

void UATLAGameInstance::GoToMainMenuLevel_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("Going To Main Menu Level"));

	UGameplayStatics::OpenLevel(GetWorld(), FName(*FString(MainMenuLevelPath)));
}

void UATLAGameInstance::CreateATLASession_Implementation(ULocalPlayer* LocalPlayer)
{
	UE_LOG(LogATLA, Display, TEXT("Creating ATLA Session"));

	FSessionSettingsInfo SessionSettingsInfo;
	SessionSettingsInfo.MapPath = GetLevelPathToOpen();
	SessionSettingsInfo.bUseLan = UCommonMultiplayerLibrary::UseLanMode(GetWorld());
	// TODO : FOR NOW SET NUMBER OF PLAYERS TO 4
	SessionSettingsInfo.NumberOfPlayers = 4;
	SessionSettingsInfo.bAllowJoinInProgress = true;
	SessionSettingsInfo.bAllowJoinViaPresenceFriendsOnly = false;
	SessionSettingsInfo.bAllowInvites = true;
	SessionSettingsInfo.bUsesPresence = true;
	SessionSettingsInfo.bIsDedicated = false;
	SessionSettingsInfo.bUsesStats = true;
	SessionSettingsInfo.bAllowJoinViaPresence = true;
	SessionSettingsInfo.bUseLobbiesIfAvailable = true;
	SessionSettingsInfo.bShouldAdvertise = true;

	UCommonMultiplayerLibrary::CreateMultiplayerSession(GetWorld(), LocalPlayer, SessionSettingsInfo);
}

void UATLAGameInstance::DestroyATLASession_Implementation()
{
	UE_LOG(LogATLA, Display, TEXT("Destroying ATLA Session"));

	UCommonMultiplayerLibrary::DestroyMultiplayerSession(GetWorld());
}

void UATLAGameInstance::FindATLASession_Implementation(const FString& LobbyName)
{
	UE_LOG(LogATLA, Display, TEXT("Finding ATLA Session %s"), *LobbyName);

	const bool bUseLan = UCommonMultiplayerLibrary::UseLanMode(GetWorld());
	UCommonMultiplayerLibrary::FindMultiplayerSession(GetWorld(), bUseLan, LobbyName);
}

FString UATLAGameInstance::GetLevelPathToOpen()
{
	return bUseTestingLevel ? TestingLevelPath : LobbyLevelPath;
}
