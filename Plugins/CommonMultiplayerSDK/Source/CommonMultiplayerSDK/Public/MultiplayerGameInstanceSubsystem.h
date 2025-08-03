// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerGameInstanceSubsystem.generated.h"

struct FSessionSettingsInfo;

/**
 *	Multiplayer Game Instance Subsystem Class.
 */
UCLASS()
class COMMONMULTIPLAYERSDK_API UMultiplayerGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerGameInstanceSubsystem();
	virtual void Deinitialize() override;

	void CreateMultiplayerSession(ULocalPlayer* LocalPlayer, FSessionSettingsInfo SessionSettingsInfo);
	void DestroyMultiplayerSession();
	void JoinMultiplayerSession(int32 LocalPlayer, const FOnlineSessionSearchResult& SessionSearchResult);
	void FindMultiplayerSession(bool bUseLan, FString LobbyName);

protected:
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnSessionInviteAccepted(bool bWasSuccessful, int32 LocalPlayer, TSharedPtr<const FUniqueNetId> PersonInviting, const FOnlineSessionSearchResult& SessionToJoin);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnFindSessionComplete(bool bWasSuccessful);

private:
	FString PathToLobby{TEXT("")};
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
	FDelegateHandle OnSessionUserInviteAcceptedDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	FDelegateHandle OnFindSessionCompleteDelegateHandle;
};
