// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiscordRPC.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "FDiscordRPCModule"

void FDiscordRPCModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if defined(DISCORD_DYNAMIC_LIB)
// Get the base directory of this plugin
    FString BaseDir = IPluginManager::Get().FindPlugin("DiscordRPC")->GetBaseDir();
    const FString SDKDir =
        FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("DiscordRPCLibrary"));
#if PLATFORM_WINDOWS
    const FString LibName = TEXT("discord-rpc");
    const FString LibDir = FPaths::Combine(*SDKDir, TEXT("Win64"));
    if (!LoadDependency(LibDir, LibName, DiscordRPCLibraryHandle)) {
        FMessageDialog::Open(
            EAppMsgType::Ok,
            LOCTEXT(LOCTEXT_NAMESPACE,
                "Failed to load DiscordRpc plugin. Plug-in will not be functional."));
        FreeDependency(DiscordRPCLibraryHandle);
    }
#endif
#endif
}

void FDiscordRPCModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
#if defined(DISCORD_DYNAMIC_LIB)
    FreeDependency(DiscordRPCLibraryHandle);
#endif
}

bool FDiscordRPCModule::LoadDependency(const FString& Dir, const FString& Name, void*& Handle)
{
    FString Lib = Name + TEXT(".") + FPlatformProcess::GetModuleExtension();
    FString Path = Dir.IsEmpty() ? *Lib : FPaths::Combine(*Dir, *Lib);

    Handle = FPlatformProcess::GetDllHandle(*Path);

    if (Handle == nullptr) {
        return false;
    }

    return true;
}

void FDiscordRPCModule::FreeDependency(void*& Handle)
{
    if (Handle != nullptr) {
        FPlatformProcess::FreeDllHandle(Handle);
        Handle = nullptr;
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDiscordRPCModule, DiscordRPC)