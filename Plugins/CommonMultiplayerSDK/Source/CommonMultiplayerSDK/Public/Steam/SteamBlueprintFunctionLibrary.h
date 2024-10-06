// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SteamBlueprintFunctionLibrary.generated.h"

class USteamGameInstanceSubsystem;
/**
 *	Steam Blueprint Function Library Class.
 */
UCLASS()
class COMMONMULTIPLAYERSDK_API USteamBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Multiplayer|Steam", meta = ( WorldContext="WorldContextObject" ))
	static bool GetSteamIsOnline(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Multiplayer|Steam", meta = ( WorldContext="WorldContextObject" ))
	static FString GetPlayerSteamName(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Multiplayer|Steam", meta = ( WorldContext="WorldContextObject" ))
	static UTexture2D* GetPlayerSteamAvatar(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "Multiplayer|Steam", meta = ( WorldContext="WorldContextObject" ))
	static void OpenSteamOverlayUI(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "Multiplayer|Steam", meta = ( WorldContext="WorldContextObject" ))
	static void OpenSteamInviteUI(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Multiplayer|Steam", meta = ( WorldContext="WorldContextObject" ))
	static int GetPlayerFriendsCount(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Multiplayer|Steam", meta = ( WorldContext="WorldContextObject" ))
	static FString GetFriendSteamName(const UObject* WorldContextObject, int FriendIndex);
	UFUNCTION(BlueprintPure, Category = "Multiplayer|Steam", meta = ( WorldContext="WorldContextObject" ))
	static UTexture2D* GetFriendSteamAvatar(const UObject* WorldContextObject, int FriendIndex);
private:
	static USteamGameInstanceSubsystem* GetSteamGameInstanceSubsystem(const UObject* WorldContextObject);
};
