// Copyright Epic Games, Inc. All Rights Reserved.

#include "Week1.h"
#include "Modules/ModuleManager.h"
#include "MyRuntimeModule/Public/MyRuntimeModule.h"
#include "Engine/Engine.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(Result, Log, All);
IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Week1, "Week1" );

// ================== 动态模块测试代码 ==================


void LoadMyModule() {
	FName ModuleName = TEXT("MyRuntimeModule");

	if (!FModuleManager::Get().IsModuleLoaded(ModuleName)) {
		//模块未加载 加载模块
		IModuleInterface* LoadedModule = FModuleManager::Get().LoadModule(ModuleName);

		if (LoadedModule) {
			//模块加载成功
			UE_LOG(Result, Log, TEXT("[week1] MyRuntime模块加载成功！"));

			//创建模块对象
			IMyRuntimeModule& MyModule = FModuleManager::GetModuleChecked<IMyRuntimeModule>(ModuleName);
			MyModule.printHello();
		}
	}
}


void UnloadMyModule() {
	FName ModuleName = TEXT("MyRuntimeModule");

	if (FModuleManager::Get().IsModuleLoaded(ModuleName)){
		//模块已加载
		FModuleManager::Get().UnloadModule(ModuleName);
		UE_LOG(Result, Log, TEXT("[week1] MyRuntime模块卸载成功！"));
	}

}

static FAutoConsoleCommand CmdLoadModule(
	TEXT("Week1.LoadModule"),
	TEXT("加载 MyRuntimeModule 模块"),
	FConsoleCommandDelegate::CreateStatic(&LoadMyModule)
);

static FAutoConsoleCommand CmdUnloadModule(
	TEXT("Week1.UnloadModule"),
	TEXT("卸载 MyRuntimeModule 模块"),
	FConsoleCommandDelegate::CreateStatic(&UnloadMyModule)
);