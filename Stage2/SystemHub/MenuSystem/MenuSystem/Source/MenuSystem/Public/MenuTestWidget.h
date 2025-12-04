#pragma once

#include "CoreMinimal.h"
#include "MenuBaseWidget.h"
#include "MenuTestWidget.generated.h"

/**
 * 一个用于测试的简单菜单 Widget，
 * 在 OnMenuOpen/OnMenuClose 被调用时立即广播对应的事件，
 * 并在 OnMenuBack 返回 false（不消费），以交由 MenuManager 处理关闭。
 */
UCLASS()
class MENUSYSTEM_API UMenuTestWidget : public UMenuBaseWidget
{
    GENERATED_BODY()

public:
    UMenuTestWidget(const FObjectInitializer& ObjInit);

    virtual void OnMenuOpen_Implementation() override;
    virtual void OnMenuClose_Implementation() override;
    virtual bool OnMenuBack_Implementation() override;
};