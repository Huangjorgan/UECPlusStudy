// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Study_ModuleEditorTarget : TargetRules
{
    public Study_ModuleEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.Add("Study_Module");
    }
}
