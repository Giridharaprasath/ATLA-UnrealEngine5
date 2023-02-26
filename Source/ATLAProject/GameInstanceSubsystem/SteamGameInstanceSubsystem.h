// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SteamGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ATLAPROJECT_API USteamGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USteamGameInstanceSubsystem();

	UFUNCTION(BlueprintCallable)
	bool GetSteamIsOnline();

	UFUNCTION(BlueprintCallable)
	FString GetPlayerSteamID();

	UFUNCTION(BlueprintCallable)
	FString GetPlayerSteamName();

	UFUNCTION(BlueprintCallable)
	void OpenSteamInviteUI();

	UFUNCTION(BlueprintCallable)
	void OpenSteamOverlayUI();

private:
	bool bSteamIsOnline { false };
	IOnlineSubsystem* SteamSubsystem;
	uint64 PlayerSteamID;
	FString PlayerSteamName;
};
