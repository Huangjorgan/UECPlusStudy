#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuTypes.h"
#include "MenuBaseWidget.generated.h"

// 声明一个动态委托，供蓝图或 C++ 绑定菜单打开/关闭完成事件
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuEvent);

/**
 * UMenuBaseWidget
 *
 * 所有菜单 Widget 的 C++ 基类，UI 由 UMG 蓝图实现继承该类。
 * 提供标准的生命周期接口（OnMenuOpened / OnMenuClosed），并带有可在蓝图中绑定的委托。
 */
UCLASS(Abstract, Blueprintable)
class MENUSYSTEM_API UMenuBaseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UMenuBaseWidget(const FObjectInitializer& ObjInit);

    /** 菜单唯一 ID（由蓝图或构造时设置） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu")
    FName MenuId;

    /** 菜单类型（可选） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu")
    EMenuType MenuType;

    /** 当菜单完全打开（例如打开动画完成）时广播 */
    UPROPERTY(BlueprintAssignable, Category="Menu|Event")
    FOnMenuEvent OnMenuOpened;

    /** 当菜单完全关闭（例如关闭动画完成）时广播 */
    UPROPERTY(BlueprintAssignable, Category="Menu|Event")
    FOnMenuEvent OnMenuClosed;

    /**
     * BlueprintNativeEvent 允许在 C++ 中提供默认实现，
     * 同时让蓝图实现覆盖或扩展行为（推荐用于播放动画）。
     */

    // 当菜单应打开时（由子系统调用），蓝图实现应播放打开动画并在动画结束时触发 OnMenuOpened.Broadcast()
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Menu")
    void OnMenuOpen();

    // 当菜单应关闭时（由子系统调用），蓝图实现应播放关闭动画并在动画结束时触发 OnMenuClosed.Broadcast()
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Menu")
    void OnMenuClose();

    // 当按下返回键（Back/Escape）时调用，若 Widget 消费该事件，返回 true；否则返回 false，交由系统 Pop 处理
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Menu")
    bool OnMenuBack();
};
