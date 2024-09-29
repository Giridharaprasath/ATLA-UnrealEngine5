// Copyright Melon Studios.

using UnrealBuildTool;

public class CommonMultiplayerSDK : ModuleRules
{
	public CommonMultiplayerSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"OnlineSubsystem",
				"OnlineSubsystemUtils",
				"OnlineSubsystemNull",
				"OnlineSubsystemSteam",
				"SteamShared",
				"Steamworks",
			}
		);
	}
}