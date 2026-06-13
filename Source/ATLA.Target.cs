// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ATLATarget : TargetRules
{
    public ATLATarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("ATLA");
    }
}
