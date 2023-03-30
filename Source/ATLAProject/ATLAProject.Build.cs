// Fill out your copyright notice in the Description page of Project Settings.

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
	}
}