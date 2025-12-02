#pragma once

#include "CoreMinimal.h"
#include "IMyUtilsInterface.h"

//日志类别声明
DECLARE_LOG_CATEGORY_EXTERN(LogMyUtils, Log, All);

class MYUTILS_API MyUtilsLibrary : public IMyUtilsInterface {
public:
    virtual void printHello() override;
};

//  模块实现类
class FMyUtilsModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    // 返回内部实现对象（非空前提下）
    IMyUtilsInterface* GetImplementation() const { return Impl.Get(); }

private:
    // 用智能指针持有实现
    TUniquePtr<IMyUtilsInterface> Impl;
};
