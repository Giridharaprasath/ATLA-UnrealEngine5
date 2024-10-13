// Copyright Melon Studios.

#include "DiscordGameInstanceSubsystem.h"

UDiscordGameInstanceSubsystem::UDiscordGameInstanceSubsystem()
{
	ClientId = 1137253192841822298;
	MinimumLogLevel = discord::LogLevel::Debug;
	CreateRetryTime = 5.0f;
}

void UDiscordGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Before we do anything else, grab a handle to the DiscordGameSDK module
	DiscordGameSDKModule = FDiscordGameSDKModule::Get();

	// Only enable subsystem ticking if the SDK was successfully loaded
	if (IsDiscordSDKLoaded())
	{
		UE_LOG(LogDiscordGameSDK, Log, TEXT("SDK loaded, enabling subsystem ticking"));

		SetTickEnabled(true);
	}
	else
	{
		UE_LOG(LogDiscordGameSDK, Error, TEXT("SDK load failed, disabling subsystem"));
	}
}

void UDiscordGameInstanceSubsystem::Deinitialize()
{
	// Stop ticking and reset the DiscordCore
	SetTickEnabled(false);
	ResetDiscordCore();

	DiscordGameSDKModule = nullptr;

	Super::Deinitialize();
}

void UDiscordGameInstanceSubsystem::SetActivity(const FDiscordActivity& Activity)
{
	if (IsDiscordRunning())
	{
		discord::ActivityAssets& Assets = CurrentActivity.GetAssets();
		discord::ActivityParty& Party = CurrentActivity.GetParty();
		discord::PartySize& PartySize = Party.GetSize();
		discord::ActivitySecrets& Secrets = CurrentActivity.GetSecrets();

		if (!Activity.State.IsEmpty())
			CurrentActivity.SetState(TCHAR_TO_ANSI(*Activity.State));

		if (!Activity.Details.IsEmpty())
			CurrentActivity.SetDetails(TCHAR_TO_ANSI(*Activity.Details));

		if (!Activity.LargeImage.IsEmpty())
			Assets.SetLargeImage(TCHAR_TO_ANSI(*Activity.LargeImage));

		if (!Activity.LargeText.IsEmpty())
			Assets.SetLargeText(TCHAR_TO_ANSI(*Activity.LargeText));

		if (!Activity.SmallImage.IsEmpty())
			Assets.SetSmallImage(TCHAR_TO_ANSI(*Activity.SmallImage));

		if (!Activity.SmallText.IsEmpty())
			Assets.SetSmallText(TCHAR_TO_ANSI(*Activity.SmallText));

		if (!Activity.PartyID.IsEmpty())
			Party.SetId(TCHAR_TO_ANSI(*Activity.PartyID));

		if (PartySize.GetCurrentSize() != Activity.PartyCurrentSize && Activity.PartyCurrentSize != 0)
			PartySize.SetCurrentSize(Activity.PartyCurrentSize);

		if (PartySize.GetMaxSize() != Activity.PartyMaxSize && Activity.PartyMaxSize != 0)
			PartySize.SetMaxSize(Activity.PartyMaxSize);

		if (!Activity.Join.IsEmpty())
			Secrets.SetJoin(TCHAR_TO_ANSI(*Activity.Join));
		
		UpdateActivity();
	}
}

void UDiscordGameInstanceSubsystem::ResetActivity()
{
	if (IsDiscordRunning())
	{
		CurrentActivity.SetState("");
		CurrentActivity.SetDetails("");

		discord::ActivityAssets& Assets = CurrentActivity.GetAssets();
		Assets.SetSmallImage("");
		Assets.SetSmallText("");

		discord::ActivityParty& Party = CurrentActivity.GetParty();
		Party.SetId("");

		discord::PartySize& PartySize = Party.GetSize();
		PartySize.SetCurrentSize(0);
		PartySize.SetMaxSize(0);

		discord::ActivitySecrets& Secrets = CurrentActivity.GetSecrets();
		Secrets.SetJoin("");

		UpdateActivity();
	}
}

void UDiscordGameInstanceSubsystem::ClearActivity()
{
	if (IsDiscordRunning())
	{
		DiscordCore().ActivityManager().ClearActivity([this](discord::Result Result)
		{
			const FString RequestDescription(TEXT("Clearing Activity"));
			LogDiscordResult(Result, RequestDescription);
		});
	}
}

void UDiscordGameInstanceSubsystem::NativeOnDiscordCoreCreated()
{
	check(DiscordCorePtr);

	DiscordCorePtr->SetLogHook(MinimumLogLevel, [this](discord::LogLevel Level, const char* RawMessage)
	{
		const FString Message(UTF8_TO_TCHAR(RawMessage));
		NativeOnDiscordLogMessage(Level, Message);
	});

	// In case we get disconnected, and we need to try to reconnect,
	// make sure we'll log any future connection errors.
	bLogConnectionErrors = true;

	// Automatically set the "Discord Rich Presence" when we get a Discord connection
	if (IsDiscordRunning())
	{
		CurrentActivity = discord::Activity{};
		CurrentActivity.SetType(discord::ActivityType::Playing);
		CurrentActivity.SetApplicationId(ClientId);
		CurrentActivity.SetSupportedPlatforms(static_cast<uint32_t>(discord::ActivitySupportedPlatformFlags::Desktop));

		discord::ActivityTimestamps& Timestamps = CurrentActivity.GetTimestamps();
		Timestamps.SetStart(FDateTime::UtcNow().ToUnixTimestamp());

		discord::ActivityAssets& Assets = CurrentActivity.GetAssets();
		Assets.SetLargeImage("gameicon");
		Assets.SetLargeText("ATLA");

		DiscordCore().ActivityManager().RegisterSteam(480);

		UpdateActivity();
	}
}

void UDiscordGameInstanceSubsystem::NativeOnDiscordCoreReset()
{
}

void UDiscordGameInstanceSubsystem::NativeOnDiscordConnectError(discord::Result Result)
{
	switch (Result)
	{
	// The InternalError result is returned when the Discord App is not running.
	case discord::Result::InternalError:
		if (bLogConnectionErrors)
		{
			UE_LOG(LogDiscordGameSDK, Warning, TEXT("Error(%i) Connecting to Discord; Discord App not running?"),
			       Result);
			// Suppress subsequent repeated log messages since we expect this to recur
			// unless/until the Discord App is restarted by the player.
			bLogConnectionErrors = false;
		}
		else
		{
			// This message may get written every 5 seconds FOREVER, so make it VeryVerbose.
			// This way you can explicitly have it appear in the output log if you want,
			// but otherwise it doesn't spam you with "Discord STILL isn't running" messages.
			UE_LOG(LogDiscordGameSDK, VeryVerbose, TEXT("Error(%i) Connecting to Discord; Discord App not running?"),
			       Result);
		}
		break;

	default:
		// Not sure what this error is...  For now, spam the output log so you notice it.
		// Once you determine exactly what it is, update this code to handle it appropriately.
		UE_LOG(LogDiscordGameSDK, Error, TEXT("Error(%i) Connecting to Discord; Unknown error"), Result);
		break;
	}
}

void UDiscordGameInstanceSubsystem::NativeOnDiscordLogMessage(discord::LogLevel Level, const FString& Message) const
{
	switch (Level)
	{
	case discord::LogLevel::Debug:
		UE_LOG(LogDiscordGameSDK, Verbose, TEXT("Discord Internal Debug: %s"), *Message);
		break;
	case discord::LogLevel::Info:
		UE_LOG(LogDiscordGameSDK, Log, TEXT("Discord Internal Message: %s"), *Message);
		break;
	case discord::LogLevel::Warn:
		UE_LOG(LogDiscordGameSDK, Warning, TEXT("Discord Internal Warning: %s"), *Message);
		break;
	case discord::LogLevel::Error:
	default:
		UE_LOG(LogDiscordGameSDK, Error, TEXT("Discord Internal Error: %s"), *Message);
		break;
	}
}

void UDiscordGameInstanceSubsystem::LogDiscordResult(discord::Result Result, const FString& RequestDescription) const
{
	switch (Result)
	{
	case discord::Result::Ok:
		UE_LOG(LogDiscordGameSDK, Log, TEXT("Success %s"), *RequestDescription);
		break;
	default:
		UE_LOG(LogDiscordGameSDK, Error, TEXT("Error(%i) %s"), Result, *RequestDescription);
		break;
	}
}

void UDiscordGameInstanceSubsystem::SetTickEnabled(bool bWantTicking)
{
	if (bWantTicking && !TickDelegateHandle.IsValid())
	{
		// Want to enable ticking and it is not currently enabled
		TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateUObject(this, &ThisClass::Tick));
	}
	else if (!bWantTicking && TickDelegateHandle.IsValid())
	{
		// Want to disable ticking and it is currently enabled
		FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
		TickDelegateHandle.Reset();
	}
}

void UDiscordGameInstanceSubsystem::UpdateActivity() const
{
	if (IsDiscordRunning())
	{
		DiscordCore().ActivityManager().UpdateActivity(CurrentActivity, [this](discord::Result Result)
		{
			const FString RequestDescription(TEXT("Updating Activity"));
			LogDiscordResult(Result, RequestDescription);
		});
	}
}

bool UDiscordGameInstanceSubsystem::Tick(float DeltaTime)
{
	if (IsDiscordRunning())
	{
		switch (const discord::Result Result = DiscordCorePtr->RunCallbacks())
		{
		case discord::Result::Ok:
			// The expected result; Discord is functioning normally
			break;

		case discord::Result::NotRunning:
			// Discord is no longer running, it is no longer usable and will never be again
			// unless/until we successfully initialize a new DiscordCore. 
			UE_LOG(LogDiscordGameSDK, Warning, TEXT("Error(%i) Running Callbacks; Discord app is no longer running"),
			       Result);
			ResetDiscordCore();
			break;

		default:
			// Unknown error, hopefully Discord can recover from this...
			// For now, we just spam the log every tick with errors so you know what is happening.
			//
			// You will need to experiment with this to determine what errors are recoverable
			// and what errors are not, and manage them better than this:
			UE_LOG(LogDiscordGameSDK, Error, TEXT("Error(%i) Running Callbacks"), Result);
			break;
		}
	}
	else if (IsDiscordSDKLoaded())
	{
		// Discord is not running, but we do have the SDK loaded.
		// Try to reconnect to DiscordCore.

		TryCreateDiscordCore(DeltaTime);
	}

	return true;
}

void UDiscordGameInstanceSubsystem::TryCreateDiscordCore(float DeltaTime)
{
	RetryWaitRemaining -= DeltaTime;

	if (RetryWaitRemaining <= 0.f)
	{
		switch (const discord::Result Result = discord::Core::Create(ClientId, DiscordCreateFlags_NoRequireDiscord,
		                                                             &DiscordCorePtr))
		{
		case discord::Result::Ok:
			UE_LOG(LogDiscordGameSDK, Log, TEXT("Created Discord Core"));
			NativeOnDiscordCoreCreated();
			break;

		default:
			NativeOnDiscordConnectError(Result);
			break;
		}

		// Don't try to create every single tick; wait some time
		RetryWaitRemaining = CreateRetryTime;
	}
}

void UDiscordGameInstanceSubsystem::ResetDiscordCore()
{
	if (DiscordCorePtr)
	{
		// Discord GameSDK doesn't provide any way to free memory !?
		//
		// It allocates memory with new() and it does not provide any way for us to free that memory.
		// If we explicitly delete, we sometimes get fatal Exception 0xc0000008, so we cannot do that.
		// Here we just have to hope that Discord isn't bad, and they free the memory on fatal errors.
		// There may be a minor memory leak here, but this shouldn't happen often during the game.
		//
		//-- delete DiscordCorePtr;
		DiscordCorePtr = nullptr;

		// Allow child classes the opportunity to react to this event
		NativeOnDiscordCoreReset();
	}

	// Ensure that next tick we'll immediately try reconnecting (if still ticking)
	RetryWaitRemaining = -1;
}
