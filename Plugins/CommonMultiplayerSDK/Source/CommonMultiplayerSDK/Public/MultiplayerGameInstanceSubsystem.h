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

protected:
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

private:
	FString PathToLobby{TEXT("")};
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
};
