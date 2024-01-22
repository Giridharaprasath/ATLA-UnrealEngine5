// Developed By Melon Studios.

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

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	void OpenSteamUserUI(int FriendIndex);

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	int GetPlayerFriendsCount();

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	int64 GetFriendSteamID(int FriendIndex);
	
	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	FString GetFriendSteamName(int FriendIndex);

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	UTexture2D* GetFriendSteamAvatar(int FriendIndex);

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	bool GetFriendPersonaState(int FriendIndex);

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	bool GetFriendGamePlayed(int FriendIndex);


	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	void SetRichPresence(FString Key, FString Value);

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	FString GetFriendRichPresence(int FriendIndex, FString Key);

	UFUNCTION(BlueprintCallable, Category = "ATLA|Steam")
	void ClearRichPresence();

private:
	bool bSteamIsOnline { false };
	IOnlineSubsystem* SteamSubsystem;
	uint64 PlayerSteamID;
	FString PlayerSteamName;
};