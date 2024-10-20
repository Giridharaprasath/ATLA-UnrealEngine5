// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DiscordGameSDK/discord-cpp/discord.h"
#include "DiscordGameSDK.h"
#include "Containers/Ticker.h"

#include "DiscordGameInstanceSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FDiscordActivity
{
	GENERATED_BODY()

	FDiscordActivity()
	{
		State = "";
		Details = "";
		LargeImage = "";
		LargeText = "";
		SmallImage = "";
		SmallText = "";
		PartyID = "";
		PartyCurrentSize = 0;
		PartyMaxSize = 0;
		Join = "";
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	FString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	FString Details;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	FString LargeImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	FString LargeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	FString SmallImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	FString SmallText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	FString PartyID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	int32 PartyCurrentSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	int32 PartyMaxSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discord")
	FString Join;
};

/**
 *	Discord Game Instance Subsystem Class.
 */
UCLASS()
class DISCORDGAMESDK_API UDiscordGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Set Class Defaults
	UDiscordGameInstanceSubsystem();

	//~USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~End of USubsystem interface

	bool IsDiscordSDKLoaded() const { return DiscordGameSDKModule && DiscordGameSDKModule->IsDiscordSDKLoaded(); }
	bool IsDiscordRunning() const { return DiscordCorePtr != nullptr; }

	FORCEINLINE_DEBUGGABLE discord::Core& DiscordCore() const
	{
		checkf(DiscordCorePtr, TEXT("Discord is not running"));
		return *DiscordCorePtr;
	}

	void SetActivity(const FDiscordActivity& Activity);
	void ResetActivity();
	void ClearActivity();

protected:
	void NativeOnDiscordCoreCreated();
	void NativeOnDiscordCoreReset();
	void NativeOnDiscordConnectError(discord::Result Result);
	void NativeOnDiscordLogMessage(discord::LogLevel Level, const FString& Message) const;
	void LogDiscordResult(discord::Result Result, const FString& RequestDescription) const;

	void SetTickEnabled(bool bWantTicking);

	uint64 ClientId;
	discord::LogLevel MinimumLogLevel;
	discord::Activity CurrentActivity;
	float CreateRetryTime;

private:
	/** Update Discord's Rich Presence Activity info */
	void UpdateActivity() const;

	bool Tick(float DeltaTime);
	void TryCreateDiscordCore(float DeltaTime);
	void ResetDiscordCore();

	/** Pointer to DiscordGameSDK plugin module */
	FDiscordGameSDKModule* DiscordGameSDKModule{nullptr};

	/** Currently-connected DiscordCore, if any */
	discord::Core* DiscordCorePtr{nullptr};

	/** Tick delegate, if ticking is currently enabled */
	FTSTicker::FDelegateHandle TickDelegateHandle;

	/** Amount of time (seconds) we will wait until trying to reconnect to Discord, if positive */
	float RetryWaitRemaining{-1.f};

	/** Toggles if/when we want to log connection errors (e.g. not repeatedly) */
	bool bLogConnectionErrors{true};
};
