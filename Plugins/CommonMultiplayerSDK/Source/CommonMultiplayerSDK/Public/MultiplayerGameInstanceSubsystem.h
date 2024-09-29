// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerGameInstanceSubsystem.generated.h"

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

private:
	TWeakPtr<IOnlineSession> SessionInterface;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
