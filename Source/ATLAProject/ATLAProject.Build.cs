// Developed By Melon Studios.

using UnrealBuildTool;

public class ATLAProject : ModuleRules
{
	public ATLAProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// Core dependencies
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
		// UMG dependencies
		PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG" });
		
		// Online Subsystem dependencies
		PublicDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemSteam", "Steamworks" });
		
		// Gameplay Ability System dependencies
		PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });
		
		// Discord RPC Plugin
		PublicDependencyModuleNames.AddRange(new string[] { "DiscordRPC" });
	}
}