// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SteamGameInstanceSubsystem.generated.h"

class IOnlineSubsystem;
/**
 *	Steam Game Instance Subsystem Class.
 */
UCLASS()
class COMMONMULTIPLAYERSDK_API USteamGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USteamGameInstanceSubsystem();

	bool GetSteamIsOnline() const;
	FString GetPlayerSteamName() const;
	UTexture2D* GetPlayerSteamAvatar() const;
	void OpenSteamOverlayUI() const;
	void OpenSteamInviteUI() const;

private:
	bool bSteamIsOnline{false};
	const IOnlineSubsystem* SteamSubsystem;
	uint64 PlayerSteamID;
	FString PlayerSteamName;
};
