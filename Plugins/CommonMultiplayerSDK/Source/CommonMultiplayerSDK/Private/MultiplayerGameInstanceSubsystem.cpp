// Copyright Melon Studios.

#include "MultiplayerGameInstanceSubsystem.h"
#include "CommonMultiplayerSDK.h"

UMultiplayerGameInstanceSubsystem::UMultiplayerGameInstanceSubsystem()
{
	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface != nullptr)
		{
			UE_LOG(LogCommonMultiplayerSDK, Display, TEXT("Subsystem Present : %s"), *Subsystem->GetSubsystemName().ToString());
		}
	}
}

void UMultiplayerGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
