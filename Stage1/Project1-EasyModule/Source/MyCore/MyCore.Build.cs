using UnrealBuildTool;

public class MyCore: ModuleRules
{
    public MyCore(ReadOnlyTargetRules Target) : base(Target)
    {
        // 指定是否使用共享或显式 PCH（推荐）
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // 公开依赖模块（供其他模块引用本模块时使用）
        PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine","MyUtils"});

        // 私有依赖模块（仅本模块内部使用）
        PrivateDependencyModuleNames.AddRange(new string[]{ });
    }
}
