// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CommonMultiplayerLibrary.generated.h"

class UMultiplayerGameInstanceSubsystem;
struct FSessionSettingsInfo;

/**
 *	Common Multiplayer Blueprint Function Library Class. 
 */
UCLASS()
class COMMONMULTIPLAYERSDK_API UCommonMultiplayerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Multiplayer", meta = ( WorldContext="WorldContextObject" ))
	static void CreateMultiplayerSession(const UObject* WorldContextObject, ULocalPlayer* LocalPlayer, FSessionSettingsInfo SessionSettingsInfo);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer", meta = ( WorldContext="WorldContextObject" ))
	static void DestroyMultiplayerSession(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer", meta = ( WorldContext="WorldContextObject" ))
	static void FindMultiplayerSession(const UObject* WorldContextObject, bool bUseLan, FString LobbyName);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer", meta = ( WorldContext="WorldContextObject" ))
	static bool UseLanMode(const UObject* WorldContextObject);

private:
	static UMultiplayerGameInstanceSubsystem* GetMultiplayerGameInstanceSubsystem(const UObject* WorldContextObject);
};
