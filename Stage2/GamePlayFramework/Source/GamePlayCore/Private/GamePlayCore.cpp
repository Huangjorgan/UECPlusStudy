#include "GamePlayCore.h"
#include "Modules/ModuleManager.h"

//// 定义日志类别
//DEFINE_LOG_CATEGORY(LogGamePlayCore);

void FGamePlayCoreModule::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("GamePlayCore Module Loaded!"));
}

void FGamePlayCoreModule::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("GamePlayCore Module Unloaded!"));
}

IMPLEMENT_MODULE(FGamePlayCoreModule, GamePlayCore)