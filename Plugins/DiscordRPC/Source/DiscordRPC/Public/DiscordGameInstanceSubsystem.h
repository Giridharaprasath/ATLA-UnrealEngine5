// Developed By Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "DiscordGameInstanceSubsystem.generated.h"

/**
 *	Discord Rich Presence Data.
 */
USTRUCT(BlueprintType)
struct FDiscordRichPresence
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString state;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString details;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	int startTimestamp = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	int endTimestamp = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString largeImageKey;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString largeImageText;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString smallImageKey;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString smallImageText;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString partyId;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	int partySize = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	int partyMax = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString matchSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString joinSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString spectateSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	bool instance = false;
};

/**
 * Discord Game Instance Subsystem Class.
 */
UCLASS()
class DISCORDRPC_API UDiscordGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Is Discord connected", Keywords = "Discord rpc"), Category = "Discord")
	bool IsConnected;
	
	UFUNCTION(BlueprintCallable, Category = "Discord")
	void InitiateDiscord(const FString& applicationId, bool autoRegister, const FString& optionalSteamId);

	UFUNCTION(BlueprintCallable, Category = "Discord")
	void ShutdownDiscord();

	UFUNCTION(BlueprintCallable, Category = "Discord")
	void UpdateDiscordPresence();

	UFUNCTION(BlueprintCallable, Category = "Discord|Set")
	void SetRPCState(const FString& CurrentState);

	UFUNCTION(BlueprintCallable, Category = "Discord|Set")
	void SetRPCDetails(const FString& CurrentDetails);

	UFUNCTION(BlueprintCallable, Category = "Discord|Set")
	void SetRPCLargeImageKey(const FString& CurrentLargeImageKey);

	UFUNCTION(BlueprintCallable, Category = "Discord|Set")
	void SetRPCLargeImageText(const FString& CurrentLargeImageText);

	UFUNCTION(BlueprintCallable, Category = "Discord|Set")
	void SetRPCSmallImageKey(const FString& CurrentSmallImageKey);

	UFUNCTION(BlueprintCallable, Category = "Discord|Set")
	void SetRPCSmallImageText(const FString& CurrentSmallImageText);
	
	UFUNCTION(BlueprintCallable, Category = "Discord|Set")
	void SetRPCPartySize(int CurrentPartySize);

	UFUNCTION(BlueprintCallable, Category = "Discord|Set")
	void SetRPCPartyMax(int CurrentPartyMax);

protected:

	void StartTimeStamp();
	
	FDiscordRichPresence RichPresence;
};