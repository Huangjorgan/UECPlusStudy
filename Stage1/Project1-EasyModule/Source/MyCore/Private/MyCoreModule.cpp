#include "MyCoreModule.h"
#include "Modules/ModuleManager.h"
#include "MyUtils/Public/MyUtilsLibrary.h"
#include "IMyUtilsInterface.h"

// 使用独立日志（静态在cpp中定义）
DEFINE_LOG_CATEGORY_STATIC(LogMyCore, Log, All);

IMPLEMENT_MODULE(FMyCoreModule, MyCore);

void FMyCoreModule::StartupModule()
{	
	UE_LOG(LogMyCore, Log, TEXT("[MyCore] MyCore module starting..."));

	if (FModuleManager::Get().IsModuleLoaded("MyUtils") || FModuleManager::Get().LoadModule("MyUtils") != nullptr) {
		//获取模块实例
		FMyUtilsModule& UtilsModule = FModuleManager::LoadModuleChecked<FMyUtilsModule>("MyUtils");
		//获取接口实现
		IMyUtilsInterface* Impl = UtilsModule.GetImplementation();

		if (Impl) {
			Impl->printHello();
			UE_LOG(LogMyCore, Warning, TEXT("[MyCore] Called MyUtils via module accessor"))
		}
		else {
			UE_LOG(LogMyCore, Error, TEXT("[MyCore] MyUtils implementation is null"));
		}
	}
	else {
		UE_LOG(LogMyCore, Error, TEXT("[MyCore] Failed to load MyUtils module"));
	}
}

void FMyCoreModule::ShutdownModule()
{
	UE_LOG(LogMyCore, Log, TEXT("[MyCore]MyCore module Shut down..."));
}
