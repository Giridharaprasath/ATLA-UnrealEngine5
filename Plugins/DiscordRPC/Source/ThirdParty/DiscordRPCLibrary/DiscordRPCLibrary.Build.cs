// Developed By Melon Studios.

using System.IO;
using UnrealBuildTool;

public class DiscordRPCLibrary : ModuleRules
{
    public DiscordRPCLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
        PublicDefinitions.Add("DISCORD_DYNAMIC_LIB=1");

        string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "DiscordRPCLibrary"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			string lib = Path.Combine(BaseDirectory, "Win64");

            PublicIncludePaths.Add(Path.Combine(BaseDirectory, "Include"));

            // Add the import library
            PublicSystemLibraryPaths.Add(lib);
            PublicAdditionalLibraries.Add(Path.Combine(lib, "discord-rpc.lib"));

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add(Path.Combine(lib, "discord-rpc.dll"));
			PublicDelayLoadDLLs.Add("discord-rpc.dll");
        }
	}
}