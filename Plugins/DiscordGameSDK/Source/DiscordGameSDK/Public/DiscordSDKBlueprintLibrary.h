// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DiscordSDKBlueprintLibrary.generated.h"

class UDiscordGameInstanceSubsystem;
struct FDiscordActivity;

/**
 *	Discord Game SDK Blueprint Function Library Class.
 */
UCLASS()
class DISCORDGAMESDK_API UDiscordSDKBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Discord", meta = ( WorldContext = "WorldContextObject" ))
	static void DiscordSetActivity(const UObject* WorldContextObject, const FDiscordActivity& DiscordActivity);
	
	UFUNCTION(BlueprintCallable, Category = "Discord", meta = ( WorldContext = "WorldContextObject" ))
	static void DiscordResetActivity(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Discord", meta = ( WorldContext = "WorldContextObject" ))
	static void DiscordClearActivity(const UObject* WorldContextObject);

private:
	static UDiscordGameInstanceSubsystem* GetDiscordGameInstanceSubsystem(const UObject* WorldContextObject);
};
