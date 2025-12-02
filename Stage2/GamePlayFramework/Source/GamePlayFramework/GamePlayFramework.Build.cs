// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamePlayFramework : ModuleRules
{
	public GamePlayFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore" ,
			"UMG",
			"GamePlayCore",
            "InterfaceCore"
        });

		PrivateDependencyModuleNames.AddRange(new string[] 
		{
            "Slate",
			"SlateCore"
        });

	}
}
