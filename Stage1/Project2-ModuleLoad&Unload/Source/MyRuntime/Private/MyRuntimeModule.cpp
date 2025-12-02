#include "MyRuntimeModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FMyRuntime, MyRuntime);
DEFINE_LOG_CATEGORY_STATIC(MyRuntime, Log, All);

void FMyRuntime::StartupModule()
{
	UE_LOG(MyRuntime,Warning,TEXT("	[MyRuntime] StartupModule() called! "))
}

void FMyRuntime::ShutdownModule()
{
	UE_LOG(MyRuntime, Warning, TEXT(" [MyRuntime] ShutdownModule called! "))
}
