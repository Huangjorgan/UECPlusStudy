#include "Study_Module.h"
#include "Modules/ModuleManager.h"
#include "Misc/OutputDevice.h"
#include "Misc/OutputDeviceDebug.h"
#include "HAL/IConsoleManager.h"

// 声明模块实现
IMPLEMENT_MODULE(FStudy_Module, Study_Module)

#define LOCTEXT_NAMESPACE "FStudy_Module"

// -----------------------------------------------------------
// 模块生命周期
// -----------------------------------------------------------
void FStudy_Module::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("[Study_Module] StartupModule() called."));
	RegisterConsoleCommands();
}

void FStudy_Module::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("[Study_Module] ShutdownModule() called."));
	UnregisterConsoleCommands();
}

// -----------------------------------------------------------
// 注册控制台命令
// -----------------------------------------------------------
void FStudy_Module::RegisterConsoleCommands()
{
	IConsoleManager& ConsoleMgr = IConsoleManager::Get();//使用引用避免拷贝，无需释放

	// ---------------------- LoadMyModule ----------------------
	ConsoleMgr.RegisterConsoleCommand(//注册函数
		TEXT("LoadMyModule"),//命名名字
		TEXT("Dynamically load module 'MyRuntimeModule'"),//帮助/描述字符串
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateStatic([](const TArray<FString>& Args, UWorld*, FOutputDevice& Ar)//创建静态委托
			{
				FName ModuleName = TEXT("MyRuntime");
				FModuleManager& Mgr = FModuleManager::Get();

				if (!Mgr.IsModuleLoaded(ModuleName))
				{
					Mgr.LoadModule(ModuleName);
					Ar.Logf(TEXT("[Console] MyRuntimeModule Loaded."));
					UE_LOG(LogTemp, Warning, TEXT("[Study_Module] MyRuntimeModule Loaded via console."));
				}
				else
				{
					Ar.Logf(TEXT("[Console] MyRuntimeModule is already loaded."));
				}
			}),
		ECVF_Default
	);

	// ---------------------- UnloadMyModule ----------------------
	ConsoleMgr.RegisterConsoleCommand(
		TEXT("UnloadMyModule"),
		TEXT("Dynamically unload module 'MyRuntimeModule'"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateStatic([](const TArray<FString>& Args, UWorld*, FOutputDevice& Ar)
			{
				FName ModuleName = TEXT("MyRuntime");
				FModuleManager& Mgr = FModuleManager::Get();

				if (Mgr.IsModuleLoaded(ModuleName))
				{
					Mgr.UnloadModule(ModuleName);
					Ar.Logf(TEXT("[Console] MyRuntimeModule Unloaded."));
					UE_LOG(LogTemp, Warning, TEXT("[Study_Module] MyRuntimeModule Unloaded via console."));
				}
				else
				{
					Ar.Logf(TEXT("[Console] MyRuntimeModule not loaded."));
				}
			}),
		ECVF_Default
	);

	// ---------------------- ToggleMyModule ----------------------
	ConsoleMgr.RegisterConsoleCommand(
		TEXT("ToggleMyModule"),
		TEXT("Toggle load/unload of 'MyRuntimeModule'"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateStatic([](const TArray<FString>& Args, UWorld*, FOutputDevice& Ar)
			{
				FName ModuleName = TEXT("MyRuntime");
				FModuleManager& Mgr = FModuleManager::Get();

				if (Mgr.IsModuleLoaded(ModuleName))
				{
					Mgr.UnloadModule(ModuleName);
					Ar.Logf(TEXT("[Console] MyRuntimeModule -> Unloaded."));
					UE_LOG(LogTemp, Warning, TEXT("[Study_Module] MyRuntimeModule -> Unloaded."));
				}
				else
				{
					Mgr.LoadModule(ModuleName);
					Ar.Logf(TEXT("[Console] MyRuntimeModule -> Loaded."));
					UE_LOG(LogTemp, Warning, TEXT("[Study_Module] MyRuntimeModule -> Loaded."));
				}
			}),
		ECVF_Default
	);

	UE_LOG(LogTemp, Warning, TEXT("[Study_Module] Console commands registered successfully."));
}

// -----------------------------------------------------------
// 注销控制台命令（可选）
// -----------------------------------------------------------
void FStudy_Module::UnregisterConsoleCommands()
{
	IConsoleManager& ConsoleMgr = IConsoleManager::Get();

	ConsoleMgr.UnregisterConsoleObject(TEXT("LoadMyModule"), false);
	ConsoleMgr.UnregisterConsoleObject(TEXT("UnloadMyModule"), false);
	ConsoleMgr.UnregisterConsoleObject(TEXT("ToggleMyModule"), false);

	UE_LOG(LogTemp, Warning, TEXT("[Study_Module] Console commands unregistered."));
}

#undef LOCTEXT_NAMESPACE
