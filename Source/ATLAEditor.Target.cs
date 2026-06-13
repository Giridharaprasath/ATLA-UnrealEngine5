// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ATLAEditorTarget : TargetRules
{
    public ATLAEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("ATLA");
    }
}
