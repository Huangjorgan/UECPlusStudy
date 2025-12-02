using UnrealBuildTool;

public class UICore : ModuleRules
{
    public UICore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "UMG",    // UI 模块必须加这个
            "GamePlayFramework"// 主模块
        });
    }
}
