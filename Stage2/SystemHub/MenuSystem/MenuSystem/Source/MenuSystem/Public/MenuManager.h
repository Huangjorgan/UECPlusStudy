#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MenuTypes.h"
#include "MenuBaseWidget.h"
#include "MenuManager.generated.h"

/**
 * UMenuManager
 *
 * 负责实际的菜单栈管理：Open / Close / Pop，并维护当前已打开菜单数组。
 * 这是一个纯 UObject，应由 UMenuSystemSubsystem 创建并托管其生命周期。
 */
UCLASS()
class MENUSYSTEM_API UMenuManager : public UObject
{
    GENERATED_BODY()

public:
    UMenuManager();

    /** 打开一个菜单，传入描述信息与世界上下文（用于 CreateWidget） */
    UFUNCTION()
    UMenuBaseWidget* OpenMenu(const FMenuDescriptor& Descriptor, UWorld* World);

    /** 关闭当前最上层菜单（会触发 Widget 的 OnMenuClose） */
    UFUNCTION()
    void CloseTopMenu();

    /** 关闭所有菜单（从栈顶逐个触发 Close） */
    UFUNCTION()
    void CloseAllMenus();

    /** 返回栈顶菜单（若无则返回 nullptr） */
    UFUNCTION()
    UMenuBaseWidget* GetTopMenu() const;

protected:
    /** 存储已创建并显示的菜单实例（按显示顺序，从底到顶） */
    UPROPERTY()
    TArray<UMenuBaseWidget*> MenuStack;

    /** 当 Widget 的 OnMenuClosed 广播时，会回到这里以移除 Widget（绑定函数） */
    UFUNCTION()
    void HandleWidgetClosed();

    /** 内部帮助：切换输入模式到 UI 并显示鼠标 */
    void EnterUIMode();

    /** 内部帮助：当栈为空时恢复游戏输入模式 */
    void ExitUIModeIfStackEmpty();
};
