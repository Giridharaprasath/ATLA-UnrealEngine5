// Copyright Melon Studios.

#include "MultiplayerGameInstanceSubsystem.h"
#include "CommonMultiplayerSDK.h"
#include "Kismet/GameplayStatics.h"

UMultiplayerGameInstanceSubsystem::UMultiplayerGameInstanceSubsystem() :
	OnCreateSessionCompleteDelegate(
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	OnStartSessionCompleteDelegate(
		FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Subsystem Present : %s"),
			       *Subsystem->GetSubsystemName().ToString());
		}
	}
}

void UMultiplayerGameInstanceSubsystem::Deinitialize()
{
	if (SessionInterface)
	{
	}
	Super::Deinitialize();
}

void UMultiplayerGameInstanceSubsystem::CreateMultiplayerSession(ULocalPlayer* LocalPlayer,
                                                                 FSessionSettingsInfo SessionSettingsInfo)
{
	if (!SessionInterface.IsValid()) return;

	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Create Session LAN : %hhd, Level : %s"), SessionSettingsInfo.bUseLan,
	       *SessionSettingsInfo.MapPath);

	if (const auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession); ExistingSession != nullptr)
	{
		// TODO : ADD Destroy Session
	}

	PathToLobby = SessionSettingsInfo.MapPath;
	OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
		OnCreateSessionCompleteDelegate);

	SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = SessionSettingsInfo.bUseLan;
	SessionSettings->NumPublicConnections = SessionSettingsInfo.NumberOfPlayers;
	SessionSettings->bAllowJoinInProgress = SessionSettingsInfo.bAllowJoinInProgress;
	SessionSettings->bAllowJoinViaPresenceFriendsOnly = SessionSettingsInfo.bAllowJoinViaPresenceFriendsOnly;
	SessionSettings->bAllowInvites = SessionSettingsInfo.bAllowInvites;
	SessionSettings->bUsesPresence = SessionSettingsInfo.bUsesPresence;
	SessionSettings->bIsDedicated = SessionSettingsInfo.bIsDedicated;
	SessionSettings->bUsesStats = SessionSettingsInfo.bUsesStats;
	SessionSettings->bAllowJoinViaPresence = SessionSettingsInfo.bAllowJoinViaPresence;
	SessionSettings->bUseLobbiesIfAvailable = SessionSettingsInfo.bUseLobbiesIfAvailable;
	SessionSettings->bShouldAdvertise = SessionSettingsInfo.bShouldAdvertise;

	SessionSettings->Set(FName("LobbyName"), LocalPlayer->GetNickname(),
	                     EOnlineDataAdvertisementType::ViaOnlineServiceAndPing, 69);

	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Session Name : %s"), *LocalPlayer->GetNickname());

	SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

void UMultiplayerGameInstanceSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("On Create Session Complete SN : %s, b : %hhd"),
	       *SessionName.ToString(), bWasSuccessful);

	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
		if (bWasSuccessful)
		{
			OnStartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
			
			SessionInterface->StartSession(SessionName);
		}
	}
}

void UMultiplayerGameInstanceSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("On Start Session Complete SN : %s, b : %hhd"),
		   *SessionName.ToString(), bWasSuccessful);

	if (SessionInterface)
	{
		SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		if (bWasSuccessful)
		{
			UGameplayStatics::OpenLevel(GetWorld(), FName(*FString(PathToLobby)), true, "?listen");
		}
	}
}
