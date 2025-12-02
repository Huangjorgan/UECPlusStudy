#include "WorldCore.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FWorldCoreModule, WorldCore)

void FWorldCoreModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("WorldCore Module Loaded!"));
}

void FWorldCoreModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("WorldCore Module Unloaded!"));
}
