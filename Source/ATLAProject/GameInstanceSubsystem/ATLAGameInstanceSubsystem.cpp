// Developed By Melon Studios.

#include "ATLAGameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

UATLAGameInstanceSubsystem::UATLAGameInstanceSubsystem() :
	OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	OnStartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete)),
	OnDestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	OnSessionUserInviteAcceptedDelegate(FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &ThisClass::OnSessionInviteAccepted)),
	OnJoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	OnFindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete))
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Blue,
					FString::Printf(TEXT("SUBSYSTEM PRESENT: %s"), *Subsystem->GetSubsystemName().ToString()));
			}

			OnSessionInviteAcceptedDelegateHandle = SessionInterface->AddOnSessionUserInviteAcceptedDelegate_Handle(OnSessionUserInviteAcceptedDelegate);
		}
	}
}

void UATLAGameInstanceSubsystem::Deinitialize()
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnSessionUserInviteAcceptedDelegate_Handle(OnSessionInviteAcceptedDelegateHandle);
	}
	Super::Deinitialize();
}

void UATLAGameInstanceSubsystem::CreateATLASession(ULocalPlayer* LocalPlayer, bool UseLan, FString LobbyPath)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, 
			FString::Printf(TEXT("Create ATLA Session LAN: %hhd, Level: %s"), UseLan, *LobbyPath));
	}

	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		DestroyATLASession();
	}
	
	//PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath);
	PathToLobby = LobbyPath;
	OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

	SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = UseLan;
	// FOR NOW ONLY 4 PLAYERS
	SessionSettings->NumPublicConnections = 4;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
	SessionSettings->bAllowInvites = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUseLobbiesIfAvailable = true;
	SessionSettings->bUsesStats = true;
	SessionSettings->bIsDedicated = false;
	SessionSettings->bAllowJoinViaPresence = true;

	SessionSettings->Set(FName("LobbyName"), LocalPlayer->GetNickname(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing, 69);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, 
			FString::Printf(TEXT("ATLA SESSION NAME : %s"), *LocalPlayer->GetNickname()));
	}
	SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

void UATLAGameInstanceSubsystem::FindATLASession(bool UseLan, FString LobbyName)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	OnFindSessionCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 100000;
	SessionSearch->bIsLanQuery = UseLan;
	SessionSearch->QuerySettings.Set(SEARCH_MINSLOTSAVAILABLE, 0, EOnlineComparisonOp::GreaterThanEquals);
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
	
	SessionSearch->QuerySettings.Set(FName("LobbyName"), LobbyName, EOnlineComparisonOp::Equals);

	FString name = LobbyName;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, 
			FString::Printf(TEXT("ATLA CREATE SESSION NAME : %s"), *LobbyName));
	}

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef()))
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegateHandle);
	}
}

void UATLAGameInstanceSubsystem::JoinATLASession(int32 LocalPlayer, const FOnlineSessionSearchResult& SessionSearchResult)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, 
			FString::Printf(TEXT("Join ATLA Session P: %d, SSR: %s"), LocalPlayer, *SessionSearchResult.GetSessionIdStr()));
	}
	
	OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
	SessionInterface->JoinSession(LocalPlayer, NAME_GameSession, SessionSearchResult);
}

void UATLAGameInstanceSubsystem::DestroyATLASession()
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, 
			FString::Printf(TEXT("Destroy ATLA Session S: %s"), LexToString(NAME_GameSession)));
	}

	OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
	SessionInterface->DestroySession(NAME_GameSession);
}

bool UATLAGameInstanceSubsystem::CheckIfPlayerInSession(ULocalPlayer* LocalPlayer)
{
	if (SessionInterface)
	{
		return SessionInterface->IsPlayerInSession(NAME_GameSession, *LocalPlayer->GetPreferredUniqueNetId());
	}

	return false;
}

void UATLAGameInstanceSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, 
		FString::Printf(TEXT("OnCreateSessionComplete SN: %s, b: %hhd"), *SessionName.ToString(), bWasSuccessful));
	}

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

void UATLAGameInstanceSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, 
		FString::Printf(TEXT("OnStartSessionComplete SN: %s, b: %hhd"), *SessionName.ToString(), bWasSuccessful));
	}

	if (SessionInterface)
	{
		SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		if (bWasSuccessful)
		{
			UGameplayStatics::OpenLevel(GetWorld(), FName(*FString(PathToLobby)), true, "?listen");
		}
	}
}

void UATLAGameInstanceSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful) 
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red,
		FString::Printf(TEXT("OnDestroySessionComplete SN: %s, b: %hhd"), *SessionName.ToString(), bWasSuccessful));
	}
}

void UATLAGameInstanceSubsystem::OnSessionInviteAccepted(bool bWasSuccessful, int32 LocalPlayer,
	TSharedPtr<const FUniqueNetId> PersonInviting, const FOnlineSessionSearchResult& SessionToJoin)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red,
		FString::Printf(TEXT("OnSessionInviteAcceptedComplete PI: %s, b: %hhd"),
			*PersonInviting->ToString(), bWasSuccessful));
	}
	
	if (bWasSuccessful)
	{
		if (SessionInterface && SessionToJoin.IsValid())
		{
			JoinATLASession(LocalPlayer, SessionToJoin);
		}
	}
}

void UATLAGameInstanceSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, 
		FString::Printf(TEXT("OnJoinSessionComplete SN: %s, R: %s"), *SessionName.ToString(), LexToString(Result)));
	}

	if (SessionInterface)
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

		FString TravelURL;
		SessionInterface->GetResolvedConnectString(NAME_GameSession, TravelURL);

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		
		if (PlayerController)
		{
			PlayerController->ClientTravel(TravelURL, TRAVEL_Absolute);
		}
	}
}

void UATLAGameInstanceSubsystem::OnFindSessionComplete(bool bWasSuccessful)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegateHandle);
	}

	if (bWasSuccessful)
	{
		for (auto Result : SessionSearch->SearchResults)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Yellow, 
				FString::Printf(TEXT("ATLA SESSIONS FOUND : %s"), *Result.Session.OwningUserName));
			}
			JoinATLASession(0, Result);

			return;
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, 
			FString::Printf(TEXT("NO ATLA SESSIONS FOUND")));
		}
	}
}