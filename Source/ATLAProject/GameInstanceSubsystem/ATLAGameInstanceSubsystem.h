// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "ATLAGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ATLAPROJECT_API UATLAGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UATLAGameInstanceSubsystem();

	// Get Player Name
	FString GetPlayerName();

	UFUNCTION(BlueprintCallable)
	bool HasOnlineSubsystem(FName Subsystem);

	UFUNCTION(BlueprintCallable)
	void CreateATLASession(bool UseLan = true, FString LobbyPath = FString(TEXT("/Game/Maps/Testing/Testing_Level")));

	UFUNCTION(BlueprintCallable)
	void DestroyATLASession();

protected:

	// Function fired when a session create request has completed
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	// Function fired when a session start request has completed
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	// Function fired when a session destroy request has completed
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

private:
	FString PlayerSteamName;
	FString PathToLobby { TEXT("") };

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	// Delegates called when session created
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	// Delegates called when session started
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	// Delegates called when session destroyed
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;


	// Handles to registered delegates for creating a session
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	// Handles to registered delegates for starting a session
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	// Handles to registered delegates for destroying a session
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
};
