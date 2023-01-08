// Fill out your copyright notice in the Description page of Project Settings.


#include "ATLAGameInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"

#include "steam/steam_api.h"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4265)
#endif

UATLAGameInstanceSubsystem::UATLAGameInstanceSubsystem() :
	OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	OnStartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete)),
	OnDestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete))
{
    if (SteamAPI_Init())
    {
        PlayerSteamName = SteamFriends()->GetPersonaName();
		if (!PlayerSteamName.IsEmpty())
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Cyan, FString::Printf(TEXT("Player Steam Name: %s"), *PlayerSteamName));
            }
        }
    }

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
		}
	}
}

FString UATLAGameInstanceSubsystem::GetPlayerName()
{
	if (!PlayerSteamName.IsEmpty())
	{
		return FString(PlayerSteamName);
	}
	return FString(TEXT(" "));
}

bool UATLAGameInstanceSubsystem::HasOnlineSubsystem(FName SubsystemName)
{
    return IOnlineSubsystem::DoesInstanceExist(SubsystemName);
}

void UATLAGameInstanceSubsystem::CreateATLASession(bool UseLan, FString LobbyPath)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, 
			FString::Printf(TEXT("Create ATLA Session with condition: %d, %s"), UseLan, *LobbyPath));
	}

	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		DestroyATLASession();
	}
	
	PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath);

	OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastSessionSettings->bIsLANMatch = UseLan;
	LastSessionSettings->NumPublicConnections = 5;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresenceFriendsOnly = true;
	LastSessionSettings->bAllowInvites = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->bUsesStats = true;

	LastSessionSettings->Set(FName("LobbyName"), PlayerSteamName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings);
}

void UATLAGameInstanceSubsystem::DestroyATLASession()
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
	SessionInterface->DestroySession(NAME_GameSession);
}

void UATLAGameInstanceSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, 
		FString::Printf(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));
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
		FString::Printf(TEXT("OnStartSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));
	}

	if (SessionInterface)
	{
		SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		if (bWasSuccessful)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				UGameplayStatics::OpenLevel(World, FName(*FString(PathToLobby)), true);
			}
		}
	}
}

void UATLAGameInstanceSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red,
		FString::Printf(TEXT("OnDestroySessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));
	}

	if (SessionInterface)
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
	}
}