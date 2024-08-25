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
		PublicDependencyModuleNames.AddRange(new [] { "UMG" });
		
		// * Discord dependencies - Discord Game SDK Plugin
		PublicDependencyModuleNames.AddRange(new string[] { "DiscordGameSDK" });
	}
}
