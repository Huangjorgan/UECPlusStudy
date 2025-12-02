using UnrealBuildTool;

public class GamePlayCore : ModuleRules
{
    public GamePlayCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InterfaceCore"
        });
    }
}
