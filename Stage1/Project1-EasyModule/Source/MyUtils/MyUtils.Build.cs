using UnrealBuildTool;

public class MyUtils : ModuleRules
{
    public MyUtils(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
        });

        PrivateDefinitions.AddRange(new string[] { });
    }
}
