// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GGRadarSystem : ModuleRules
{
	public GGRadarSystem(ReadOnlyTargetRules Target) : base(Target)
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
				"UMG",
				"DeveloperSettings"
			}
			);
	}
}
