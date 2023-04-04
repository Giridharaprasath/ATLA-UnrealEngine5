// Developed By Melon Studios.

using UnrealBuildTool;
using System.Collections.Generic;

public class ATLAProjectEditorTarget : TargetRules
{
	public ATLAProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ATLAProject" } );
	}
}