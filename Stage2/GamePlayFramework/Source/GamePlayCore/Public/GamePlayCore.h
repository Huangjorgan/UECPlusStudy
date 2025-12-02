#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

//// 对外声明日志类别，供整个模块使用
//DECLARE_LOG_CATEGORY_EXTERN(LogGamePlayCore, Log, All);

class FGamePlayCoreModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
