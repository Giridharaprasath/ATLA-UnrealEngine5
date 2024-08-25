// Copyright Melon Studios.

using System.IO;
using UnrealBuildTool;

public class DiscordGameSDKLibrary : ModuleRules
{
	public DiscordGameSDKLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "discord_game_sdk.dll.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("discord_game_sdk.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dll", "$(PluginDir)/Source/ThirdParty/DiscordGameSDKLibrary/Win64/discord_game_sdk.dll");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "discord_game_sdk.dylib"));
			RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dylib", "$(PluginDir)/Source/ThirdParty/DiscordGameSDKLibrary/Mac/discord_game_sdk.dylib");
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string soPath = "$(PluginDir)/Source/ThirdParty/DiscordGameSDKLibrary/Linux/discord_game_sdk.so";
			PublicAdditionalLibraries.Add(soPath);
			PublicDelayLoadDLLs.Add(soPath);
			RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.so", soPath);
		}
	}
}