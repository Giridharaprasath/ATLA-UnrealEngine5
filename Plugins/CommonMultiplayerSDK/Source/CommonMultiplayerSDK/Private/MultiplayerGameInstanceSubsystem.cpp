// Copyright Melon Studios.

#include "MultiplayerGameInstanceSubsystem.h"
#include "CommonMultiplayerSDK.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSessionSettings.h"

UMultiplayerGameInstanceSubsystem::UMultiplayerGameInstanceSubsystem() :
	OnCreateSessionCompleteDelegate(
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	OnStartSessionCompleteDelegate(
		FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete)),
	OnDestroySessionCompleteDelegate(
		FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	OnSessionUserInviteAcceptedDelegate(
		FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &ThisClass::OnSessionInviteAccepted)),
	OnJoinSessionCompleteDelegate(
		FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	OnFindSessionsCompleteDelegate(
		FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete))
{
	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Subsystem Present : %s"),
			       *Subsystem->GetSubsystemName().ToString());
		}

		OnSessionUserInviteAcceptedDelegateHandle = SessionInterface->AddOnSessionUserInviteAcceptedDelegate_Handle(
			OnSessionUserInviteAcceptedDelegate);
	}
}

void UMultiplayerGameInstanceSubsystem::Deinitialize()
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnSessionUserInviteAcceptedDelegate_Handle(OnSessionUserInviteAcceptedDelegateHandle);
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
		DestroyMultiplayerSession();
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

void UMultiplayerGameInstanceSubsystem::DestroyMultiplayerSession()
{
	if (!SessionInterface.IsValid()) return;

	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Destroy Session : %s"), LexToString(NAME_GameSession));

	OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(
		OnDestroySessionCompleteDelegate);
	SessionInterface->DestroySession(NAME_GameSession);
}

void UMultiplayerGameInstanceSubsystem::JoinMultiplayerSession(int32 LocalPlayer,
                                                               const FOnlineSessionSearchResult& SessionSearchResult)
{
	if (!SessionInterface.IsValid()) return;

	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Join Session Player : %d, SSR : %s"), LocalPlayer,
	       *SessionSearchResult.GetSessionIdStr());

	OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
		OnJoinSessionCompleteDelegate);
	SessionInterface->JoinSession(LocalPlayer, NAME_GameSession, SessionSearchResult);
}

void UMultiplayerGameInstanceSubsystem::FindMultiplayerSession(bool bUseLan, FString LobbyName)
{
	if (!SessionInterface.IsValid()) return;

	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Find Session Name : %s, LAN : %hhd"), *LobbyName, bUseLan);

	OnFindSessionCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
		OnFindSessionsCompleteDelegate);

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 1000000;
	SessionSearch->bIsLanQuery = bUseLan;
	SessionSearch->QuerySettings.Set(SEARCH_MINSLOTSAVAILABLE, 0, EOnlineComparisonOp::GreaterThanEquals);
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

	if (!bUseLan)
		SessionSearch->QuerySettings.Set(FName("LobbyName"), LobbyName, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef()))
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegateHandle);
	}
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
			OnStartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(
				OnStartSessionCompleteDelegate);

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

void UMultiplayerGameInstanceSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("On Destroy Session Complete SN : %s, b : %hhd"),
	       *SessionName.ToString(), bWasSuccessful);
}

void UMultiplayerGameInstanceSubsystem::OnSessionInviteAccepted(bool bWasSuccessful, int32 LocalPlayer,
                                                                TSharedPtr<const FUniqueNetId> PersonInviting,
                                                                const FOnlineSessionSearchResult& SessionToJoin)
{
	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("On Session User Invite Accept Complete PI : %s, b : %hhd"),
	       *PersonInviting->ToString(), bWasSuccessful);

	if (bWasSuccessful)
	{
		if (SessionInterface && SessionToJoin.IsValid())
		{
			JoinMultiplayerSession(LocalPlayer, SessionToJoin);
		}
	}
}

void UMultiplayerGameInstanceSubsystem::OnJoinSessionComplete(FName SessionName,
                                                              EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("On Join Session Complete PI : %s, b : %s"),
	       *SessionName.ToString(), LexToString(Result));

	if (SessionInterface)
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

		FString TravelURL;
		SessionInterface->GetResolvedConnectString(NAME_GameSession, TravelURL);

		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			PlayerController->ClientTravel(TravelURL, TRAVEL_Absolute);
		}
	}
}

void UMultiplayerGameInstanceSubsystem::OnFindSessionComplete(bool bWasSuccessful)
{
	UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("On Find Session Complete b : %hhd, C : %d"), bWasSuccessful,
	       SessionSearch->SearchResults.Num());
	
	if (SessionInterface)
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegateHandle);

		if (bWasSuccessful)
		{
			for (auto Result : SessionSearch->SearchResults)
			{
				UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Session Found : %s"), *Result.Session.OwningUserName);

				JoinMultiplayerSession(0, Result);
				return;
			}
		}
		else
		{
			UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("No Sessions Found"));
		}
	}
}
