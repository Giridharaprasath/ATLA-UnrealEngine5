// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ATLA : ModuleRules
{
    public ATLA(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine", "InputCore",
            "EnhancedInput"]);
    }
}
