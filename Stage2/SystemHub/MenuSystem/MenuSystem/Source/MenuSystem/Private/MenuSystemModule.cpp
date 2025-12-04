#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"

class FMenuSystemModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        // 模块启动时可以放置日志/注册编辑器扩展等
        UE_LOG(LogTemp, Log, TEXT("MenuSystem module Loaded.")); 
    }

    virtual void ShutdownModule() override
    {
        UE_LOG(LogTemp, Log, TEXT("MenuSystem module shutdown.")); 
    }
};

IMPLEMENT_MODULE(FMenuSystemModule, MenuSystem)
