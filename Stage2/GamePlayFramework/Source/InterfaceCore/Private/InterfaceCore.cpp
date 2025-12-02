#include "InterfaceCore.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FInterfaceCoreModule, InterfaceCore)

void FInterfaceCoreModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("InterfaceCore Module Loaded!"));
}

void FInterfaceCoreModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("InterfaceCore Module Unloaded!"));
}
