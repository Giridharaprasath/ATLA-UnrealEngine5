// Copyright Melon Studios.

#include "CommonMultiplayerSDK.h"

DEFINE_LOG_CATEGORY(LogCommonMultiplayerSDK);

#define LOCTEXT_NAMESPACE "FCommonMultiplayerSDKModule"

void FCommonMultiplayerSDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCommonMultiplayerSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCommonMultiplayerSDKModule, CommonMultiplayerSDK)