// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SteamGameInstanceSubsystem.generated.h"

/**
 * Steam Game Instance Subsystem Class.
 */
UCLASS()
class ATLAPROJECT_API USteamGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USteamGameInstanceSubsystem();

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	bool GetSteamIsOnline();

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	FString GetPlayerSteamID();

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	FString GetPlayerSteamName();

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	UTexture2D* GetPlayerSteamAvatar();

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	void OpenSteamInviteUI();

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	void OpenSteamOverlayUI();

private:
	bool bSteamIsOnline { false };
	IOnlineSubsystem* SteamSubsystem;
	uint64 PlayerSteamID;
	FString PlayerSteamName;
};