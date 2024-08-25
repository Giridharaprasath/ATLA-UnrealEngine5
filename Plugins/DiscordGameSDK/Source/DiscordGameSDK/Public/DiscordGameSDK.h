// Copyright Melon Studios.

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDiscordGameSDK, Log, All);

class FDiscordGameSDKModule : public IModuleInterface
{
public:
	/** Name of this Module*/
	static const FName ModuleName;

	/**
	 * @return Pointer to FDiscordGameModule, if it has been loaded into the Engine, else nullptr
	 */
	static FDiscordGameSDKModule* Get()
	{
		return static_cast<FDiscordGameSDKModule*>(FModuleManager::Get().GetModule(ModuleName));
	}

	/**
	 * @return TRUE if we successfully loaded the Discord GameSDK DLL; else FALSE
	 */
	FORCEINLINE bool IsDiscordSDKLoaded() const { return DiscordGameSDKHandle != nullptr; }

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	/**
	 * Get the path to the Discord GameSDK DLL for the current platform.
	 * @return Absolute path to the Discord GameSDK DLL we need to load
	 */
	FString GetPathToDLL() const;

private:
	/** Handle to the dll we will load */
	void* DiscordGameSDKHandle {nullptr};
};
