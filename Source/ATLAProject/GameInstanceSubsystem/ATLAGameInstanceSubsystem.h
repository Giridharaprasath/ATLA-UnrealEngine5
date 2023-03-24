// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "ATLAGameInstanceSubsystem.generated.h"

/**
 * ATLA Game Instance Subsystem Class
 */
UCLASS()
class ATLAPROJECT_API UATLAGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UATLAGameInstanceSubsystem();
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "ATLA")
	void CreateATLASession(ULocalPlayer* LocalPlayer, bool UseLan = true,
		FString LobbyPath = FString(TEXT("/Game/Maps/Testing/Testing_Level")));

	UFUNCTION(BlueprintCallable, Category = "ATLA")
	void DestroyATLASession();

	void JoinATLASession(int32 LocalPlayer, const FOnlineSessionSearchResult& SessionSearchResult);

	UFUNCTION(BlueprintCallable, Category = "ATLA")
	bool CheckIfPlayerInSession(ULocalPlayer* LocalPlayer);


protected:

	// Function fired when a session create request has completed
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	// Function fired when a session start request has completed
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	// Function fired when a session destroy request has completed
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	// Function fired when a session invite request has accepted
	void OnSessionInviteAccepted(bool bWasSuccessful, int32 LocalPlayer, TSharedPtr<const FUniqueNetId> PersonInviting,
		const FOnlineSessionSearchResult& SessionToJoin);
	// Function fires when a session join request has completed
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	FString PathToLobby { TEXT("") };

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;

	// Delegates called when session created
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	// Delegates called when session started
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	// Delegates called when session destroyed
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	// Delegates called when session invite accepted
	FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;
	// Delegates called when session joined
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	// Handles to registered delegates for creating a session
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	// Handles to registered delegates for starting a session
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	// Handles to registered delegates for destroying a session
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
	// Handles to registered delegates for accepting a session invite
	FDelegateHandle OnSessionInviteAcceptedDelegateHandle;
	// Handles to registered delegates for joining a session
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
};
