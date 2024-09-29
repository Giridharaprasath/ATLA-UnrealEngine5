// Copyright Melon Studios.

using UnrealBuildTool;

public class ATLA : ModuleRules
{
	public ATLA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// * Core dependencies
		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		// * Gameplay Ability System dependencies
		PublicDependencyModuleNames.AddRange(new[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });

		// * UMG dependencies
		PublicDependencyModuleNames.AddRange(new[] { "UMG" });

		// * Common UI
		PublicDependencyModuleNames.AddRange(new string[] { "CommonInput", "CommonUI" });

		// * Online Subsystem dependencies
		PublicDependencyModuleNames.AddRange(new string[]
			{ "OnlineSubsystem", "OnlineSubsystemSteam", "OnlineSubsystemUtils", "Steamworks" });

		// * Discord Game SDK Plugin
		PublicDependencyModuleNames.AddRange(new string[] { "DiscordGameSDK" });

		// * Common Multiplayer SDK Plugin
		PublicDependencyModuleNames.AddRange(new string[] { "CommonMultiplayerSDK" });
	}
}