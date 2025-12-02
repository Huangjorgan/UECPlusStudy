
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWidgetPCInterface.generated.h"

/**
 * Widget与PC交互的接口
 */

 // 生成 UInterface
UINTERFACE(MinimalAPI)
class UWidgetPCInterface : public UInterface
{
    GENERATED_BODY()
};

// 继承 UInterface 的接口类
class GAMEPLAYFRAMEWORK_API IWidgetPCInterface
{
    GENERATED_BODY()

public:
    // 接口函数，Widget 可以调用
    virtual void ToggleTimeoutMenu() = 0;
    virtual void Back2StartMenu() = 0;
};
