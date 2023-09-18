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
	FString State;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString Details;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	int StartTimestamp = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	int EndTimestamp = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString LargeImageKey;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString LargeImageText;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString SmallImageKey;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString SmallImageText;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString PartyId;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	int PartySize = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	int PartyMax = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString MatchSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString JoinSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	FString SpectateSecret;
	UPROPERTY(BlueprintReadWrite, Category = "Discord")
	bool bInstance = false;
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
	void InitiateDiscord(const FString& ApplicationID, bool bAutoRegister, const FString& SteamID);

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

	UFUNCTION(BlueprintCallable, Category = "Discord|Reset")
	void ResetDiscordPresence();

protected:

	void StartTimeStamp();
	
	FDiscordRichPresence RichPresence;
};