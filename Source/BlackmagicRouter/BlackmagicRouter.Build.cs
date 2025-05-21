// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using EpicGames.Core;

public class BlackmagicRouter : ModuleRules
{
	public BlackmagicRouter(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Networking",
            "Sockets"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
        });
    }
}
