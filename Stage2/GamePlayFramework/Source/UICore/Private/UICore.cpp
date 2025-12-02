#include "UICore.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FUICoreModule, UICore)

void FUICoreModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("UICore Module Loaded!"));
}

void FUICoreModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("UICore Module Unloaded!"));
}