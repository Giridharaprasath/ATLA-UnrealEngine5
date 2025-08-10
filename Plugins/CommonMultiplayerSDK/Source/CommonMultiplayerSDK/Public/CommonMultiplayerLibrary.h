// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CommonMultiplayerLibrary.generated.h"

DECLARE_DELEGATE_OneParam(FOnSessionProcessSignature, const bool /* bIsSuccessful */);

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
	UFUNCTION(Category = "Multiplayer", meta = ( WorldContext = "WorldContextObject" ))
	static void CreateMultiplayerSession(const UObject* WorldContextObject, ULocalPlayer* LocalPlayer, const FSessionSettingsInfo SessionSettingsInfo);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer", meta = ( WorldContext = "WorldContextObject" ))
	static void DestroyMultiplayerSession(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer", meta = ( WorldContext = "WorldContextObject" ))
	static void FindMultiplayerSession(const UObject* WorldContextObject, bool bUseLan, const FString LobbyName);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer", meta = ( WorldContext = "WorldContextObject" ))
	static bool UseLanMode(const UObject* WorldContextObject);

	static FOnSessionProcessSignature OnCreateStartSessionProcessDelegate;
	static FOnSessionProcessSignature OnFindJoinSessionProcessDelegate;

private:
	static UMultiplayerGameInstanceSubsystem* GetMultiplayerGameInstanceSubsystem(const UObject* WorldContextObject);
};
